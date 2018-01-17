#include "WeatherListener.h"

void WeatherListener::key(String key) {
  if (key == "icon") {
    this->in_icon = true;
  } else {
    this->in_icon = false;
  }
  if (key == "temperatureMax") {
    this->in_temperatureMax = true;
  } else {
    this->in_temperatureMax = false;
  }
  if (key == "temperatureMin") {
    this->in_temperatureMin = true;
  } else {
    this->in_temperatureMin = false;
  }
  if (key == "data") {
    this->in_data = true;
  }
  if (key == "summary") {
    this->in_summary = true;
  } else {
    this->in_summary = false;
  }

}

void WeatherListener::value(String value) {
  if (this->in_data && this->in_icon && !this->got_icon) {
    this->icon = value;
    this->got_icon = true;
  }
  if (this->in_temperatureMax && !this->got_temperatureMax) {
    this->temperatureMax = value.toInt();
    this->got_temperatureMax = true;
  }
  if (this->in_temperatureMin && !this->got_temperatureMin) {
    this->temperatureMin = value.toInt();
    this->got_temperatureMin = true;
  }
  if (this->in_summary) {
    if (this->in_data && !this->got_summary_daily) {
      this->summary_daily = value;
      this->got_summary_daily = true;
    }
    if (!this->in_data && !this->got_summary_weekly) {
       this->summary_weekly = value;
       this->got_summary_weekly = true;
    }
  }
}

void WeatherListener::endArray() {
  if (this->in_data) {
    this->in_data = false;
  }
}

