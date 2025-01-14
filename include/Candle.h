#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>

struct Candle {
	
	struct Date {
		std::chrono::_V2::system_clock::time_point timepoint;

		Date() {}

		// Converts from "YYYY-MM-DD HH:MM:SS"
		Date(const std::string& datetime) {
			std::tm tm = {};
			std::stringstream ss(datetime);
			ss >> std::get_time(&tm, "%Y-%m-%D %H:%M:%S");
			timepoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
		}

		bool isDayDifferent(const Date& other) const {
			auto tt = std::chrono::system_clock::to_time_t(timepoint);
			auto ttOther = std::chrono::system_clock::to_time_t(other.timepoint);

			return gmtime(&tt)->tm_wday != gmtime(&ttOther)->tm_wday;
		}
	};

	std::vector<std::string> descriptions;

	double open = 0;
	double close = 0;
	double high = 0;
	double low = 0;
	double volume = 0;
	Date datetime;

	int number = -1;

	double vwap = 0;

	Candle() {}

	// Pass Datetime as "%Y-%m-%d %H:%M:%S"
	Candle(double open, double close, double high, double low, double volume,
		const Date& datetime, int number = -1, double vwap = 0) : 
		open(open),
		close(close),
		high(high),
		low(low),
		volume(volume),
		datetime(datetime),
		number(number),
		vwap(vwap) {

	}

	double relativeLocation(double value) const {
		return (value - low) / (high - low);
	}

	bool doji() const {
		return abs(open - close) / (high - low) < .25;
	}

	bool flatBottom() const {
		return (std::min)(open, close) == low;
	}

	bool flatTop() const {
		return (std::max)(open, close) == low;
	}
};
