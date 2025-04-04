#pragma once
#include "WinElement.hpp"

namespace Win52 {
	struct Time {
		u16 hour = 0, min = 0, sec = 0, ms = 0;
	};

	class Date {
	public:
		i32 year = 0;
		u8 month = 0;
		u8 day = 1;
		Time time;
		Date(u8 month = 0, u8 day = 0, i32 year = 0) {
			this->month = month;
			this->day = day;
			this->year = year;
		}
		Date(Time t, u8 month = 0, u8 day = 0, i32 year = 0) {
			this->time = t;
			this->month = month;
			this->day = day;
			this->year = year;
		}
		SYSTEMTIME getSysTime() {
			return {
				.wYear = (WORD)(this->year & 0xffff),
				.wMonth = (WORD)(this->month),
				.wDayOfWeek = (WORD)(this->day % 7),
				.wDay = (WORD)(this->day),
				.wHour = (WORD)(this->time.hour),
				.wMinute = (WORD)(this->time.min),
				.wSecond = (WORD)(this->time.sec),
				.wMilliseconds = (WORD)(this->time.ms)
			};
		}
	};

	class Calendar : public WinElement {
	private:
		void HWNDCreate() override;
	public:
		Calendar(Win52::Window* win, WinId id, int x = -1, int y = -1, int w = -1, int h = -1);
		Calendar(Win52::WinContainer* wContain, WinId id, int x = -1, int y = -1, int w = -1, int h = -1);
		void SetDate(Date d);
		Date GetSelectedDate();
	};

	class DateInput : public WinElement {
	private:
		void HWNDCreate() override;
	public:
		DateInput(Win52::Window* win, WinId id, int x = -1, int y = -1, int w = -1, int h = -1);
		DateInput(Win52::WinContainer* wContain, WinId id, int x = -1, int y = -1, int w = -1, int h = -1);
	};
}