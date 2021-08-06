#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class CarSize: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow {

public:
	virtual void onLoad();
	virtual void onUnload();

	void GameStart(std::string eventName);
	void AddCar(std::string eventName);
	
	bool isEnabled();
	void changeCarSize();
	float getCarScale();

	const float scale_min = 0.1;
	const float scale_max = 5.0;
	const float scale_default = 1.0;

	//Gui function
	void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;
};
