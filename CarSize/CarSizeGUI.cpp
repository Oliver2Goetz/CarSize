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
    ImGui::TextUnformatted("I would recommend a value between 0.8 and 1.6x inclusive. Outside that range the hitboxes and physics are sometimes messed up.");

    renderWidgetsBlue();
    ImGui::Separator();
    renderWidgetsOrange();
}

void CarSize::renderWidgetsBlue() {
    //Enable Checkbox
    CVarWrapper enableCvar = cvarManager->getCvar("car_size_enabled_blue");
    if (!enableCvar) { return; }

    bool enabledBlue = enableCvar.getBoolValue();
    if (ImGui::Checkbox("Enable plugin for blue", &enabledBlue)) {
        enableCvar.setValue(enabledBlue);
        gameWrapper->Execute([this](GameWrapper* gw) {
            clickEnable();
        });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Toggle CarSize Plugin for blue");
    }

    //Size Slider
    CVarWrapper sizeCvar = cvarManager->getCvar("car_size_scale_blue");
    if (!sizeCvar) { return; }

    float sizeBlue = sizeCvar.getFloatValue();
    if (ImGui::SliderFloat("Scale for blue", &sizeBlue, SCALE_MIN, SCALE_MAX, "%.1f")) {
        sizeCvar.setValue(sizeBlue);
    }
    if (ImGui::IsItemHovered()) {
        std::string hoverText = "Scale is x" + std::to_string(sizeBlue);
        ImGui::SetTooltip(hoverText.c_str());
    }

    //Apply Button
    if (ImGui::Button("Apply for blue")) {
        gameWrapper->Execute([this](GameWrapper* gw) {
            cvarManager->executeCommand("change_car_size_blue");
        });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Apply configured settings");
    }
}

void CarSize::renderWidgetsOrange() {
    //Enable Checkbox
    CVarWrapper enableCvar = cvarManager->getCvar("car_size_enabled_orange");
    if (!enableCvar) { return; }

    bool enabledOrange = enableCvar.getBoolValue();
    if (ImGui::Checkbox("Enable plugin for orange", &enabledOrange)) {
        enableCvar.setValue(enabledOrange);
        gameWrapper->Execute([this](GameWrapper* gw) {
            clickEnable();
        });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Toggle CarSize Plugin for orange");
    }

    //Size Slider
    CVarWrapper sizeCvar = cvarManager->getCvar("car_size_scale_orange");
    if (!sizeCvar) { return; }

    float sizeOrange = sizeCvar.getFloatValue();
    if (ImGui::SliderFloat("Scale for orange", &sizeOrange, SCALE_MIN, SCALE_MAX, "%.1f")) {
        sizeCvar.setValue(sizeOrange);
    }
    if (ImGui::IsItemHovered()) {
        std::string hoverText = "Scale is x" + std::to_string(sizeOrange);
        ImGui::SetTooltip(hoverText.c_str());
    }

    //Apply Button
    if (ImGui::Button("Apply for orange")) {
        gameWrapper->Execute([this](GameWrapper* gw) {
            cvarManager->executeCommand("change_car_size_orange");
        });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Apply configured settings");
    }
}
