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
    bool got_summary_daily;
    bool got_summary_weekly;
    
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
        got_summary_daily(false),
        got_summary_weekly(false),
        JsonListener() { }

    String icon;
    uint8_t temperatureMax;
    uint8_t temperatureMin;
    String summary_daily;
    String summary_weekly;

    void whitespace(char c) {};
  
    void startDocument() {};

    virtual void key(String key);

    virtual void value(String value);

    virtual void endArray();

    void endObject() {};

    void endDocument() {};

    void startArray() {};

    void startObject() {};
};
