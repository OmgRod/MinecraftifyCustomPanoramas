#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <Geode/loader/Loader.hpp>

using namespace geode::prelude;

$execute {
    static const std::unordered_map<std::string, std::string> panoramaBaseMap = {
        { "The Garden Awakens", "thegardenawakens" },
        { "Tricky Trials", "trickytrials" },
        { "Trails & Tales", "trailsandtales" },
        { "The Wild", "thewild" },
        // { "Caves and Cliffs II", "cavesandcliffsii" },
        // { "Caves and Cliffs I", "cavesandcliffsi" },
        { "The Nether", "thenether" },
        { "Buzzy Bees", "buzzybees" },
        { "Village & Pillage", "villageandpillage" }
    };

    auto mod = Loader::get()->getLoadedMod("zalphalaneous.minecraft");
    if (mod) {
        // Execute the panorama logic at startup
        std::string value = mod->getSettingValue<std::string>("panorama");
        if (panoramaBaseMap.contains(value)) {
            std::string base = panoramaBaseMap.at(value);
            for (int i = 0; i < 6; ++i) {
                mod->setSavedValue(fmt::format("panorama-{}", i), fmt::format("{}_panorama_{}.png"_spr, base, i));
            }
            mod->setSavedValue("changed", true);
        }

        // Listen for future changes in the "panorama" setting
        listenForSettingChanges("panorama", [mod](std::string value) {
            if (panoramaBaseMap.contains(value)) {
                std::string base = panoramaBaseMap.at(value);
                for (int i = 0; i < 6; ++i) {
                    mod->setSavedValue(fmt::format("panorama-{}", i), fmt::format("{}_panorama_{}.png"_spr, base, i));
                }
                mod->setSavedValue("changed", true);
            }
        });
    }
}
