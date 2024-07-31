#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <functional>
#include "Candle.h"

namespace Timeframe {
	enum {
		ONE_MINUTE,
		FIVE_MINUTE,
		FIFTEEN_MINUTE,
		THIRTY_MINUTE,
		ONE_HOUR,
		FOUR_HOUR,
		ONE_DAY,
		ONE_WEEK
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
		default: return {};
		}
	}
}

class MarketData {
private:

	typedef const std::vector<Candle>& Data;

	typedef std::function<void(Data)> DataUpdate;

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