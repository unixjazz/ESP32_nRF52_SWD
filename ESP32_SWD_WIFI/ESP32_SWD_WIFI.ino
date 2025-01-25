/*
   Copyright (c) 2021 Aaron Christophel ATCnetz.de
   SPDX-License-Identifier: GPL-3.0-or-later
*/
#include <WiFi.h>
#include <WebServer.h>
#include "web.h"
#include "glitcher.h"
#include "nrf_swd.h"
#include "swd.h"
#include "secrets.h"

void setup()
{
  // Serial init
  Serial.begin(115200);
  delay(2000);

  // WiFi init
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME, AP_PASSWD);
  Serial.printf("Initializing the WiFi AP: ");
  Serial.println(AP_NAME);
  init_web();

  // SWD init
  swd_begin();
  glitcher_begin();
  Serial.printf("SWD Id: 0x%08x\r\n", nrf_begin());
}

void loop()
{
  if (get_glitcher()) {
    do_glitcher();
  }
  else {
    do_nrf_swd();
  }
}
