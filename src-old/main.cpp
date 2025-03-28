#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <vector>
#include <memory>

#include "GDHistoryProvider.hpp"

namespace LHSettings {
	std::vector<std::shared_ptr<LevelProvider>> providers;
};

#include "ProviderPopup.hpp"

#include <Geode/modify/LevelSearchLayer.hpp>
class $modify(LHLevelSearchLayer, LevelSearchLayer) {
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) {
			return false;
		}

		// auto winSize = CCDirectory::sharedInstance()

		auto logo = CCSprite::create("GDPSLogo.png"_spr);
		auto extrasearch = CCMenuItemSpriteExtra::create(
			logo,
			this,
			menu_selector(LHLevelSearchLayer::onMyButton)
		);

		auto menu = (CCMenu *)this->getChildByID("other-filter-menu");

		auto app = CCApplication::sharedApplication();
		auto platform = app->getTargetPlatform();

		if (platform != TargetPlatform::kTargetAndroid) {
			menu->addChild(extrasearch);
			menu->updateLayout();
		} else {
			extrasearch->setID("provider-button"_spr);

			auto children = menu->getChildren();

			auto last_child = (CCNode *)children->lastObject();
			auto pos = last_child->getPosition();
			auto csz = last_child->getContentSize();

			pos.y -= csz.width + 10.f;

			extrasearch->setPosition(pos);

			menu->addChild(extrasearch);
		}

		return true;
	}

	void onMyButton(CCObject*) {
		ProviderPopup *popup = ProviderPopup::create(LHSettings::providers);

		// addChild(popup, 500);
	}
};

$execute {
	LHSettings::providers.push_back(std::make_shared<GDHistoryProvider>());
}