// overly_described: Kyubu port of ToufouMaster's OverlyDescribedCubeWorld.
//
// When you interact with a decorative object the game prints "There is nothing special". This mod replaces that text
// with a description based on the object's type (the table is in descriptions.inc).
//
// At 0x4881AC the game does `push 0x701DB8` (the "nothing special" string) and then `mov [ebp-4], 0` (0x4881B1).
// [ebp+8] is a pointer to the object's type id. The old mod patched in a stub that pushed its own text; here a
// mid-function hook runs right after the push and overwrites the pushed pointer on the stack ([esp]) instead.
#include "../common.hpp"

#include <map>

namespace {

const std::map<int, const wchar_t*> kDescriptions{
#include "descriptions.inc"
};

const KyubuApi* g_api = nullptr;

void KYUBU_CALL on_interact(KyubuCpuContext* ctx, void*) {
    uint32_t object = 0;
    int32_t type = 0;
    if (g_api->mem_read(ctx->ebp + 8, &object, sizeof object) != KY_OK || !object) return;
    if (g_api->mem_read(object, &type, sizeof type) != KY_OK) return;
    const auto it = kDescriptions.find(type);
    if (it == kDescriptions.end()) return;   // unknown type: the game's own text stays
    *reinterpret_cast<const wchar_t**>(ctx->esp) = it->second;
}

}  // namespace

struct OverlyDescribed {
    explicit OverlyDescribed(kyubu::Mod& m) {
        g_api = m.api();
        const uintptr_t site = classic::at(m, 0x881B1);
        // the instruction before it must be the push of the default string
        static const uint8_t want_push[] = {0x68, 0xB8, 0x1D, 0x70, 0x00};   // push <address of the string>: relocated (ASLR)
        static const uint8_t want_site[] = {0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00};
        if (!classic::expect(m, classic::at(m, 0x881AC), want_push, sizeof want_push, "overly_described (push)", "x????") ||
            !classic::expect(m, site, want_site, sizeof want_site, "overly_described (site)"))
            return;
        KyubuId id = 0;
        const KyubuResult r = m.api()->hook_mid(m.handle(), site, &on_interact, nullptr, &id);
        if (r != KY_OK) { m.error("overly_described: could not hook the object interaction (result %d)", static_cast<int>(r)); return; }
        m.info("overly_described: %d object descriptions loaded", static_cast<int>(kDescriptions.size()));
    }
};

KYUBU_MOD("overly_described", KY_SIDE_CLIENT, OverlyDescribed)
