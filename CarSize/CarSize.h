#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
#include <math.h>

constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class CarSize: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow {

public:
	virtual void onLoad();
	virtual void onUnload();

	void GameStart(std::string eventName);
	void AddCar(std::string eventName);

	bool isEnabledBlue();
	bool isEnabledOrange();
	bool isActiveTeam(int team_num_2);

	void changeCarSize(bool forceChange = false);
	float getCarScale(int team_num_2);
	float getMassByCarScale(float car_scale);
	
	int TEAM_NUM_BLUE = 0;
	int TEAM_NUM_ORANGE = 1;

	const float SCALE_MIN = 0.1;
	const float SCALE_MAX = 5.0;
	const float SCALE_DEFAULT = 1.0;

	void clickEnable();

	//Gui function
	void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;

	void renderWidgetsBlue();
	void renderWidgetsOrange();
};
