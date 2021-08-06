#include "pch.h"
#include "CarSize.h"


BAKKESMOD_PLUGIN(CarSize, "This plugins lets you change the scale of all the cars in the lobby", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void CarSize::onLoad() {
	_globalCvarManager = cvarManager;

	//Register CVars
	cvarManager->registerCvar("car_size_enabled", "0", "Enable CarSize", true, true, 0, true, 1);
	cvarManager->registerCvar("car_size_scale", "1.0", "The scale of the cars (Default: 1x)", true, true, scale_min, true, scale_max);

	//Register Notifiers
	cvarManager->registerNotifier("change_car_size", [this](std::vector<std::string> args) {
		changeCarSize();
	}, "", PERMISSION_ALL);

	//Event-Hooks
	gameWrapper->HookEvent("Function GameEvent_TA.Countdown.BeginState", bind(&CarSize::GameStart, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_TA.AddCar", bind(&CarSize::AddCar, this, std::placeholders::_1));
}

void CarSize::onUnload() {
}

void CarSize::GameStart(std::string eventName) {
	changeCarSize();
}

void CarSize::AddCar(std::string eventName) {
	changeCarSize();
}

void CarSize::changeCarSize(bool forceChange) {
	if (!isEnabled() && !forceChange) { return; }

	ServerWrapper sw = gameWrapper->GetGameEventAsServer();
	if (!sw) { return; }

	ArrayWrapper<PriWrapper> pris = sw.GetPRIs();
	for (int i = 0; i < pris.Count(); i++) {
		PriWrapper priw = pris.Get(i);

		CarWrapper car = priw.GetCar();
		if (!car) { return; }

		float car_size = getCarScale();
		car.SetCarScale(car_size);
	}
}

float CarSize::getCarScale() {
	if (!isEnabled()) { return 1.0; };

	CVarWrapper sizeCvar = cvarManager->getCvar("car_size_scale");
	if (!sizeCvar) { return scale_default; }

	return sizeCvar.getFloatValue();
}

bool CarSize::isEnabled() {
	CVarWrapper enableCvar = cvarManager->getCvar("car_size_enabled");
	if (!enableCvar) { return false; }

	return enableCvar.getBoolValue();
}

/*
 * This makes sure to reset it back to 1x if disabled.
 */
void CarSize::clickEnable() {
	changeCarSize(true);
}
