#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <Geode/loader/Loader.hpp>

using namespace geode::prelude;

$execute {
    listenForSettingChanges("panorama", [](std::string value) {
        static const std::unordered_map<std::string, std::string> panoramaBaseMap = {
            { "The Garden Awakens", "thegardenawakens" },
            { "Tricky Trials", "trickytrials" },
            { "Trails & Tales", "trailsandtales" },
            { "The Wild", "thewild" },
            { "Caves & Cliffs: Part II", "cavesandcliffs2" },
            { "Caves & Cliffs: Part I", "cavesandcliffs1" },
            { "The Nether", "thenether" },
            { "Buzzy Bees", "buzzybees" },
        };

        auto mod = Loader::get()->getLoadedMod("zalphalaneous.minecraft");
        if (mod && panoramaBaseMap.contains(value)) {
            std::string base = panoramaBaseMap.at(value);
            for (int i = 0; i < 6; ++i) {
                mod->setSavedValue(fmt::format("panorama-{}", i), fmt::format("{}_panorama_{}.png"_spr, base, i));
            }
            mod->setSavedValue("changed", true);
        }
    });
}
