#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <functional>
#include "Candle.h"

namespace Timeframe {
	enum : int {
		ONE_MINUTE = 60,
		FIVE_MINUTE = 60 * 5,
		FIFTEEN_MINUTE = 60 * 15,
		THIRTY_MINUTE = 60 * 30,
		ONE_HOUR = 60 * 60,
		FOUR_HOUR = 60 * 60 * 4,
		ONE_DAY = 60 * 60 * 24,
		ONE_WEEK = 60 * 60 * 24 * 7
	};

	inline static std::string str(int index) {
		switch (index) {
		case ONE_MINUTE: return "M1";
		case FIVE_MINUTE: return "M5";
		case FIFTEEN_MINUTE: return "M15";
		case THIRTY_MINUTE: return "M30";
		case ONE_HOUR: return "H1";
		case FOUR_HOUR: return "H4";
		case ONE_DAY: return "D1";
		case ONE_WEEK: return "W1";
		default: return "";
		}
	}
}

class MarketData {
private:

	typedef std::function<void(const MarketData&)> DataUpdate;

	mutable std::vector<DataUpdate> onNewBar_;
	mutable std::vector<DataUpdate> onUpdate_;
	mutable std::vector<DataUpdate> onReload_;

	mutable std::mutex mtx_;

public:

	MarketData(const std::vector<Candle>& candles, int timeframe, const std::string& symbol);

	MarketData();

	std::vector<Candle> candles;

	std::string symbol;

	std::atomic_int timeframe;

	std::mutex& mtx();

	void newBar();
	void update();
	void reload();

	void onNewBar(DataUpdate) const;
	void onUpdate(DataUpdate) const;
	void onReload(DataUpdate) const;
};