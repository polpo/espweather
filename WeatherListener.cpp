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
  if (key == "summary") {
    this->in_summary = true;
  } else {
    this->in_summary = false;
  }
}

void WeatherListener::value(String value) {
  if (this->in_icon && !this->got_icon) {
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
  if (this->in_summary && !this->got_summary) {
    this->summary = value;
    this->got_summary = true;
  }
}

