#include "pch.h"
#include "CarSize.h"


BAKKESMOD_PLUGIN(CarSize, "This plugins lets you change the scale of all the cars in the lobby", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void CarSize::onLoad() {
	_globalCvarManager = cvarManager;

	//Register CVars
	cvarManager->registerCvar("car_size_enabled", "0", "Enable CarSize", true, true, 0, true, 1);
	cvarManager->registerCvar("car_size_scale", "1.0", "The scale of the cars (Default: 1x)", true, true, scale_min, true, scale_max);
	cvarManager->registerCvar("car_size_mass", "1000", "The mass", true, true, 0.0, true, 1000.0);

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

		float mass = getMassByCarScale(car_size);
		car.SetMass(mass);

		//Debug Testing
		//CVarWrapper massCvar = cvarManager->getCvar("car_size_mass");
		//if (!massCvar) { return; }
		//car.SetMass(massCvar.getFloatValue());
	}
}

float CarSize::getCarScale() {
	if (!isEnabled()) { return 1.0; };

	CVarWrapper sizeCvar = cvarManager->getCvar("car_size_scale");
	if (!sizeCvar) { return scale_default; }

	return sizeCvar.getFloatValue();
}

/*
 * Fancy function to get the manually written mass of the given car size :D
 */
float CarSize::getMassByCarScale(float car_size) {
	float mass = 185.0f;
	float rounded = roundf(car_size * 100) / 100;

	if (rounded == 1.00) {
		mass = 185.0f;
	}

	if (rounded == 1.100000f) {
		mass = 175.0f;
	} else if (rounded == 1.200000f) {
		mass = 165.5f;
	} else if (rounded == 1.300000f) {
		mass = 153.0f;
	} else if (rounded == 1.400000f) {
		mass = 142.75f;
	} else if (rounded == 1.500000f) {
		mass = 133.75f;
	} else if (rounded == 1.600000f) {
		mass = 129.5f;
	} else if (rounded == 1.700000f) {
		mass = 127.0f;
	} else if (rounded == 1.800000f) {
		mass = 120.5f;
	} else if (rounded == 1.900000f) {
		mass = 115.5f;
	} else if (rounded == 2.000000f) {
		mass = 111.5f;
	} else if (rounded == 2.100000f) {
		mass = 107.5f;
	} else if (rounded == 2.200000f) {
		mass = 103.5f;
	} else if (rounded == 2.300000f) {
		mass = 100.0f;
	} else if (rounded == 2.400000f) {
		mass = 97.5f;
	} else if (rounded == 2.500000f) {
		mass = 93.5f;
	} else if (rounded == 2.600000f) {
		mass = 89.5f;
	} else if (rounded == 2.700000f) {
		mass = 87.0f;
	} else if (rounded == 2.800000f) {
		mass = 85.5f;
	} else if (rounded == 2.900000f) {
		mass = 83.5f;
	} else if (rounded == 3.000000f) {
		mass = 81.0f;
	} else if (rounded == 3.100000f) {
		mass = 78.5f;
	} else if (rounded == 3.200000f) {
		mass = 76.0f;
	} else if (rounded == 3.300000f) {
		mass = 74.5f;
	} else if (rounded == 3.400000f) {
		mass = 72.5f;
	} else if (rounded == 3.500000f) {
		mass = 71.0f;
	} else if (rounded == 3.600000f) {
		mass = 69.0f;
	} else if (rounded == 3.700000f) {
		mass = 67.5f;
	} else if (rounded == 3.800000f) {
		mass = 66.0f;
	} else if (rounded == 3.900000f) {
		mass = 65.0f;
	} else if (rounded == 4.000000f) {
		mass = 63.0f;
	} else if (rounded == 4.100000f) {
		mass = 61.5f;
	} else if (rounded == 4.200000f) {
		mass = 60.5f;
	} else if (rounded == 4.300000f) {
		mass = 59.0f;
	} else if (rounded == 4.400000f) {
		mass = 58.0f;
	} else if (rounded == 4.500000f) {
		mass = 56.5f;
	} else if (rounded == 4.600000f) {
		mass = 55.0f;
	} else if (rounded == 4.700000f) {
		mass = 54.0f;
	} else if (rounded == 4.800000f) {
		mass = 53.0f;
	} else if (rounded == 4.900000f) {
		mass = 52.5f;
	} else if (rounded == 5.000000f) {
		mass = 51.5f;
	}

	if (rounded == 0.900000f) {
		mass = 195.5f;
	} else if (rounded <= 0.800000f) {
		//0.8 and less are not supported - mass values won't change from here on for the cars :(
	}

	cvarManager->log("CARSIZE - Set mass " + std::to_string(mass) + " for scale " + std::to_string(rounded));

	return mass;
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
