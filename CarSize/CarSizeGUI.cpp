#include "pch.h"
#include "CarSize.h"

void CarSize::SetImGuiContext(uintptr_t ctx) {
    ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

std::string CarSize::GetPluginName() {
    return "Car Size";
}

void CarSize::RenderSettings() {
    //Text
    ImGui::TextUnformatted("I would recommend a value between 0.3 and 2.2x inclusive. Outside that range the hitboxes are too messed up.");

    //Enable Checkbox
    CVarWrapper enableCvar = cvarManager->getCvar("car_size_enabled");
    if (!enableCvar) { return; }

    bool enabled = enableCvar.getBoolValue();
    if (ImGui::Checkbox("Enable plugin", &enabled)) {
        enableCvar.setValue(enabled);
        gameWrapper->Execute([this](GameWrapper* gw) {
            clickEnable();
        });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Toggle CarSize Plugin");
    }

    //Size Slider
    CVarWrapper sizeCvar = cvarManager->getCvar("car_size_scale");
    if (!sizeCvar) { return; }

    float size = sizeCvar.getFloatValue();
    if (ImGui::SliderFloat("Scale", &size, scale_min, scale_max, "%.1f")) {
        sizeCvar.setValue(size);
    }
    if (ImGui::IsItemHovered()) {
        std::string hoverText = "Scale is x" + std::to_string(size);
        ImGui::SetTooltip(hoverText.c_str());
    }

    //TEST MASS SLIDER
    /*CVarWrapper massCvar = cvarManager->getCvar("car_size_mass");
    if (!massCvar) { return; }

    float mass = massCvar.getFloatValue();
    if (ImGui::SliderFloat("Mass (TEST)", &mass, 0, 1000.0)) {
        massCvar.setValue(mass);
    }
    if (ImGui::IsItemHovered()) {
        std::string hoverText = "Mass is " + std::to_string(mass);
        ImGui::SetTooltip(hoverText.c_str());
    }*/

    //Apply Button
    if (ImGui::Button("Apply")) {
        gameWrapper->Execute([this](GameWrapper* gw) {
            cvarManager->executeCommand("change_car_size");
        });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Apply configured settings");
    }
}
