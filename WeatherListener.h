#pragma once

#include <JsonListener.h>

class WeatherListener: public JsonListener {
  private:
    bool in_data;
    bool in_icon;
    bool got_icon;
    bool in_temperatureMin;
    bool got_temperatureMin;
    bool in_temperatureMax;
    bool got_temperatureMax;
    bool in_summary;
    bool got_summary;

  public:
    WeatherListener()
      : in_data(false),
        in_icon(false),
        got_icon(false),
        in_temperatureMin(false),
        got_temperatureMin(false),
        in_temperatureMax(false),
        got_temperatureMax(false),
        in_summary(false),
        got_summary(false),
        JsonListener() { }

    String icon;
    uint8_t temperatureMax;
    uint8_t temperatureMin;
    String summary;

    void whitespace(char c) {};
  
    void startDocument() {};

    virtual void key(String key);

    virtual void value(String value);

    void endArray() {};

    void endObject() {};

    void endDocument() {};

    void startArray() {};

    void startObject() {};
};
