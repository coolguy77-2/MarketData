#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>

struct Candle {

public:

	std::vector<std::string> descriptions;

	double open = 0;
	double close = 0;
	double high = 0;
	double low = 0;
	double vwap = 0;

	double volume = 0;

	int number = -1;

	boost::posix_time::ptime datetime;

	bool mouseHovering = false;

	Candle() {}

	Candle(double open, double close, double high, double low, double volume,
		std::string datetime, int number = -1, double vwap = 0) : 
		open(open),
		close(close),
		high(high),
		low(low),
		vwap(vwap),
		volume(volume),
		number(number) {

		this->datetime = boost::posix_time::time_from_string(datetime);
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
