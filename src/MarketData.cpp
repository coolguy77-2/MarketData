#include "MarketData.h"

MarketData::MarketData() {
	timeframe = Timeframe::ONE_DAY;
}

MarketData::MarketData(const std::vector<Candle>& c, int tf, const std::string& s)
	: candles(c), timeframe(tf), symbol(s) {
		
}

std::mutex& MarketData::mtx() {
	return mtx_;
}

void MarketData::newBar() {
	for (const auto& callback : onNewBar_) {
		callback(*this);
	}
}

void MarketData::update() {
	for (const auto& callback : onUpdate_) {
		callback(*this);
	}
}

void MarketData::reload() {
	for (const auto& callback : onReload_) {
		callback(*this);
	}
}

void MarketData::onNewBar(MarketData::DataUpdate update) const {
	std::lock_guard<std::mutex> lck(mtx_);
	onNewBar_.push_back(update);
}

void MarketData::onUpdate(MarketData::DataUpdate update) const {
	std::lock_guard<std::mutex> lck(mtx_);
	onUpdate_.push_back(update);
}

void MarketData::onReload(MarketData::DataUpdate update) const {
	std::lock_guard<std::mutex> lck(mtx_);
	onReload_.push_back(update);
}