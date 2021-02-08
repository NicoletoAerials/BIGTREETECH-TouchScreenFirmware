#include "FeatureSettings.h"
#include "includes.h"

LISTITEMS featureSettingsItems = {
  // title
  LABEL_FEATURE_SETTINGS,
  // icon                   ItemType      Item Title          item value text(only for custom value)
  {
    {ICONCHAR_BACKGROUND,   LIST_LABEL,   LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {ICONCHAR_BACKGROUND,   LIST_LABEL,   LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {ICONCHAR_BACKGROUND,   LIST_LABEL,   LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {ICONCHAR_BACKGROUND,   LIST_LABEL,   LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {ICONCHAR_BACKGROUND,   LIST_LABEL,   LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {ICONCHAR_PAGEUP,       LIST_LABEL,   LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {ICONCHAR_PAGEDOWN,     LIST_LABEL,   LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {ICONCHAR_BACK,         LIST_LABEL,   LABEL_BACKGROUND,   LABEL_BACKGROUND},
  }
};

//
//parameter values
//

const uint16_t iconToggle[ITEM_TOGGLE_NUM] =
{
  ICONCHAR_TOGGLE_OFF,
  ICONCHAR_TOGGLE_ON
};

#define ITEM_TOGGLE_AUTO_NUM 3
const LABEL itemToggleAuto[ITEM_TOGGLE_AUTO_NUM] =
{
  LABEL_OFF,
  LABEL_ON,
  LABEL_AUTO
};

#define ITEM_TOGGLE_SMART_NUM 3
const LABEL itemToggleSmart[ITEM_TOGGLE_SMART_NUM] =
{
  LABEL_OFF,
  LABEL_ON,
  LABEL_SMART
};

#define ITEM_DEFAULT_MODE_NUM 2
const char *const itemDefaultMode[ITEM_DEFAULT_MODE_NUM] =
{
  //item value text(only for custom value)
  "Marlin",
  "Touch"
};

#define ITEM_MARLIN_TYPE_NUM 2
const char *const itemMarlinType[ITEM_MARLIN_TYPE_NUM] =
{
  //item value text(only for custom value)
  "LCD2004",
  "LCD12864"
};

#define ITEM_NOTIFICATION_TYPE_NUM 3
const char *const itemNotificationType[ITEM_NOTIFICATION_TYPE_NUM] =
{
  //item value text(only for custom value)
  "OFF",
  "POPUP",
  "TOAST"
};

//
//add key number index of the items
//
typedef enum
{
  SKEY_STATUS_SCREEN = 0,
  SKEY_TERMINAL_ACK,
  SKEY_INVERT_X_AXIS,
  SKEY_INVERT_Y_AXIS,
  SKEY_INVERT_Z_AXIS,
  SKEY_PERSISTENT_INFO,
  SKEY_FILE_LIST_MODE,
  SKEY_ACK_NOTIFICATION,
  SKEY_DEFAULT_MODE,
  SKEY_SERIAL_ALWAYS_ON,

  #ifdef ST7920_SPI
    SKEY_MARLIN_SHOW_TITLE,
    SKEY_MARLIN_FULLSCREEN,
    SKEY_MARLIN_TYPE,
  #endif

  SKEY_SPEED,
  SKEY_AUTO_LOAD_LEVELING,
  SKEY_TOUCHMI_SENSOR,
  SKEY_ONBOARD_SD_SUPPORT,
  SKEY_M27_ALWAYS_ACTIVE,
  SKEY_LONG_FILENAME_SUPPORT,
  SKEY_FAN_SPEED_PERCENT,
  SKEY_XY_OFFSET_PROBING,
  SKEY_Z_STEPPERS_ALIGNMENT,

  #ifdef PS_ON_PIN
    SKEY_PS_ON,
    SKEY_PS_ON_ACTIVE_HIGH,
  #endif

  #ifdef FIL_RUNOUT_PIN
    SKEY_FIL_RUNOUT,
    SKEY_FIL_RUNOUT_INVERTING,
  #endif

  SKEY_PL_RECOVERY_EN,
  SKEY_PL_RECOVERY_HOME,
  SKEY_BTT_MINI_UPS,

  #ifdef LED_COLOR_PIN
    SKEY_KNOB_LED_COLOR,

    #ifdef LCD_LED_PWM_CHANNEL
      SKEY_KNOB_LED_IDLE,
    #endif
  #endif

  #ifdef LCD_LED_PWM_CHANNEL
    SKEY_LCD_BRIGHTNESS,
    SKEY_LCD_IDLE_BRIGTHNESS,
    SKEY_LCD_IDLE_DELAY,
  #endif

  SKEY_START_GCODE_ENABLED,
  SKEY_END_GCODE_ENABLED,
  SKEY_CANCEL_GCODE_ENABLED,
  SKEY_RESET_SETTINGS, // Keep reset always at the bottom of the settings menu list.
  SKEY_COUNT //keep this always at the end
}SKEY_LIST;

#define FE_PAGE_COUNT  (SKEY_COUNT+LISTITEM_PER_PAGE-1)/LISTITEM_PER_PAGE
int fe_cur_page = 0;

//
//set item types
//
LISTITEM settingPage[SKEY_COUNT] = {
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_STATUS_SCREEN,           LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_TERMINAL_ACK,            LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_INVERT_X_AXIS,           LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_INVERT_Y_AXIS,           LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_INVERT_Z_AXIS,           LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_PERSISTENT_INFO,         LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_FILE_LIST_MODE,          LABEL_BACKGROUND},
  {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_ACK_NOTIFICATION,        LABEL_DYNAMIC},
  {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_DEFAULT_MODE,            LABEL_DYNAMIC},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_SERIAL_ALWAYS_ON,        LABEL_BACKGROUND},

  #ifdef ST7920_SPI
    {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_MARLIN_SHOW_TITLE,       LABEL_BACKGROUND},
    {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_MARLIN_FULLSCREEN,       LABEL_BACKGROUND},
    {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_MARLIN_TYPE,             LABEL_DYNAMIC},
  #endif

  {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_MOVE_SPEED,              LABEL_NORMAL},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_AUTO_LOAD_LEVELING,      LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_TOUCHMI_SENSOR,          LABEL_BACKGROUND},
  {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_ONBOARD_SD_SUPPORT,      LABEL_OFF},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_M27_ALWAYS_ACTIVE,       LABEL_BACKGROUND},
  {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_LONG_FILENAME_SUPPORT,   LABEL_OFF},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_FAN_SPEED_PERCENT,       LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_XY_OFFSET_PROBING,       LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_Z_STEPPERS_ALIGNMENT,    LABEL_BACKGROUND},

  #ifdef PS_ON_PIN
    {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_PS_ON,                   LABEL_OFF},
    {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_PS_ON_ACTIVE_HIGH,       LABEL_BACKGROUND},
  #endif

  #ifdef FIL_RUNOUT_PIN
    {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_FIL_RUNOUT,              LABEL_OFF},
    {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_FIL_RUNOUT_INVERTING,    LABEL_BACKGROUND},
  #endif

  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_PL_RECOVERY_EN,          LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_PL_RECOVERY_HOME,        LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_BTT_MINI_UPS,            LABEL_BACKGROUND},

  #ifdef LED_COLOR_PIN
    {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_KNOB_LED_COLOR,          LABEL_OFF},

    #ifdef LCD_LED_PWM_CHANNEL
      {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_KNOB_LED_IDLE,           LABEL_BACKGROUND},
    #endif
  #endif

  #ifdef LCD_LED_PWM_CHANNEL
    {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_LCD_BRIGHTNESS,          LABEL_DYNAMIC},
    {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_LCD_IDLE_BRIGHTNESS,     LABEL_DYNAMIC},
    {ICONCHAR_BLANK,       LIST_CUSTOMVALUE,   LABEL_LCD_IDLE_DELAY,          LABEL_DYNAMIC},
  #endif

  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_START_GCODE_ENABLED,     LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_END_GCODE_ENABLED,       LABEL_BACKGROUND},
  {ICONCHAR_TOGGLE_ON,   LIST_TOGGLE,        LABEL_CANCEL_GCODE_ENABLED,    LABEL_BACKGROUND},
  // Keep reset settings always at the bottom of the settings menu list.
  {ICONCHAR_BLANK,       LIST_MOREBUTTON,    LABEL_SETTINGS_RESET,          LABEL_BACKGROUND}
};

void resetSettings(void)
{
  infoSettingsReset();
  storePara();
  popupReminder(DIALOG_TYPE_SUCCESS, LABEL_INFO, LABEL_SETTINGS_RESET_DONE);
}

//
//perform action on button press
//
void updateFeatureSettings(uint8_t key_val)
{
  uint8_t item_index = fe_cur_page*LISTITEM_PER_PAGE+ key_val;

  switch (item_index)
  {
    case SKEY_STATUS_SCREEN:
      infoSettings.status_screen = (infoSettings.status_screen + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.status_screen];
      break;

    case SKEY_TERMINAL_ACK:
      infoSettings.terminalACK = (infoSettings.terminalACK + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.terminalACK];
      break;

    case SKEY_INVERT_X_AXIS:
      infoSettings.invert_axis[X_AXIS] = (infoSettings.invert_axis[X_AXIS] + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.invert_axis[X_AXIS]];
     break;

    case SKEY_INVERT_Y_AXIS:
      infoSettings.invert_axis[Y_AXIS] = (infoSettings.invert_axis[Y_AXIS] + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.invert_axis[Y_AXIS]];
      break;

    case SKEY_INVERT_Z_AXIS:
      infoSettings.invert_axis[Z_AXIS] = (infoSettings.invert_axis[Z_AXIS] + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.invert_axis[Z_AXIS]];
      break;

    case SKEY_PERSISTENT_INFO:
      infoSettings.persistent_info = (infoSettings.persistent_info + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.persistent_info];
      break;

    case SKEY_FILE_LIST_MODE:
      infoSettings.file_listmode = (infoSettings.file_listmode + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.file_listmode];
      break;

    case SKEY_ACK_NOTIFICATION:
      infoSettings.ack_notification = (infoSettings.ack_notification + 1) % ITEM_NOTIFICATION_TYPE_NUM;
      setDynamicTextValue(key_val, (char *)itemNotificationType[infoSettings.ack_notification]);
      break;

    case SKEY_DEFAULT_MODE:
      infoSettings.mode = (infoSettings.mode + 1) % ITEM_DEFAULT_MODE_NUM;
      setDynamicTextValue(key_val, (char *)itemDefaultMode[infoSettings.mode]);
      break;

    case SKEY_SERIAL_ALWAYS_ON:
      infoSettings.serial_alwaysOn = (infoSettings.serial_alwaysOn + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.serial_alwaysOn];
      break;

    #ifdef ST7920_SPI
      case SKEY_MARLIN_SHOW_TITLE:
        infoSettings.marlin_mode_showtitle = (infoSettings.marlin_mode_showtitle + 1) % ITEM_TOGGLE_NUM;
        settingPage[item_index].icon = iconToggle[infoSettings.marlin_mode_showtitle];
        break;

      case SKEY_MARLIN_FULLSCREEN:
        infoSettings.marlin_mode_fullscreen = (infoSettings.marlin_mode_fullscreen + 1) % ITEM_TOGGLE_NUM;
        settingPage[item_index].icon = iconToggle[infoSettings.marlin_mode_fullscreen];
        break;

      case SKEY_MARLIN_TYPE:
        infoSettings.marlin_type = (infoSettings.marlin_type + 1) % ITEM_MARLIN_TYPE_NUM;
        setDynamicTextValue(key_val, (char *)itemMarlinType[infoSettings.marlin_type]);
        break;
    #endif

    case SKEY_SPEED:
      infoSettings.move_speed = (infoSettings.move_speed + 1) % ITEM_SPEED_NUM;
      settingPage[item_index].valueLabel = itemSpeed[infoSettings.move_speed].label;
      break;

    case SKEY_AUTO_LOAD_LEVELING:
      infoSettings.auto_load_leveling = (infoSettings.auto_load_leveling + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.auto_load_leveling];
      break;

    case SKEY_TOUCHMI_SENSOR:
      infoSettings.touchmi_sensor = (infoSettings.touchmi_sensor + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.touchmi_sensor];
      break;

    case SKEY_ONBOARD_SD_SUPPORT:
        infoSettings.onboardSD = (infoSettings.onboardSD + 1) % ITEM_TOGGLE_AUTO_NUM;
        settingPage[item_index].valueLabel = itemToggleAuto[infoSettings.onboardSD];
        break;

    case SKEY_M27_ALWAYS_ACTIVE:
      infoSettings.m27_active = (infoSettings.m27_active + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.m27_active];
      break;

    case SKEY_LONG_FILENAME_SUPPORT:
        infoSettings.longFileName = (infoSettings.longFileName + 1) % ITEM_TOGGLE_AUTO_NUM;
        settingPage[item_index].valueLabel = itemToggleAuto[infoSettings.longFileName];
        break;

    case SKEY_FAN_SPEED_PERCENT:
      infoSettings.fan_percentage = (infoSettings.fan_percentage + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.fan_percentage];
      break;

    case SKEY_XY_OFFSET_PROBING:
      infoSettings.xy_offset_probing = (infoSettings.xy_offset_probing + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.xy_offset_probing];
      break;

    case SKEY_Z_STEPPERS_ALIGNMENT:
      infoSettings.z_steppers_alignment = (infoSettings.z_steppers_alignment + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.z_steppers_alignment];
      break;

    #ifdef PS_ON_PIN
      case SKEY_PS_ON:
        infoSettings.auto_off = (infoSettings.auto_off + 1) % ITEM_TOGGLE_AUTO_NUM;
        settingPage[item_index].valueLabel = itemToggleAuto[infoSettings.auto_off];
        break;

      case SKEY_PS_ON_ACTIVE_HIGH:
        infoSettings.powerloss_invert = (infoSettings.powerloss_invert + 1) % ITEM_TOGGLE_NUM;
        settingPage[item_index].icon = iconToggle[infoSettings.powerloss_invert];
        break;
    #endif

    #ifdef FIL_RUNOUT_PIN
      case SKEY_FIL_RUNOUT:
        infoSettings.runout = (infoSettings.runout + 1) % ITEM_TOGGLE_SMART_NUM;
        settingPage[item_index].valueLabel = itemToggleSmart[infoSettings.runout];
        break;

      case SKEY_FIL_RUNOUT_INVERTING:
        infoSettings.runout_invert = (infoSettings.runout_invert + 1) % ITEM_TOGGLE_NUM;
        settingPage[item_index].icon = iconToggle[infoSettings.runout_invert];
        break;
    #endif

    case SKEY_PL_RECOVERY_EN:
      infoSettings.powerloss_en = (infoSettings.powerloss_en + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.powerloss_en];
      break;

    case SKEY_PL_RECOVERY_HOME:
      infoSettings.powerloss_home = (infoSettings.powerloss_home + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.powerloss_home];
      break;

    case SKEY_BTT_MINI_UPS:
      infoSettings.btt_ups = (infoSettings.btt_ups + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.btt_ups];
      break;

    #ifdef LED_COLOR_PIN
      case SKEY_KNOB_LED_COLOR:
        infoSettings.knob_led_color = (infoSettings.knob_led_color + 1 ) % LED_COLOR_NUM;
        settingPage[item_index].valueLabel = itemLedcolor[infoSettings.knob_led_color];
        WS2812_Send_DAT(led_color[infoSettings.knob_led_color]);
        break;

      #ifdef LCD_LED_PWM_CHANNEL
        case SKEY_KNOB_LED_IDLE:
          infoSettings.knob_led_idle = (infoSettings.knob_led_idle + 1) % ITEM_TOGGLE_NUM;
          settingPage[item_index].icon = iconToggle[infoSettings.knob_led_idle];
          break;
      #endif //LCD_LED_PWM_CHANNEL
    #endif

    #ifdef LCD_LED_PWM_CHANNEL
      case SKEY_LCD_BRIGHTNESS:
      {
        infoSettings.lcd_brightness = (infoSettings.lcd_brightness + 1) % ITEM_BRIGHTNESS_NUM;

        if (infoSettings.lcd_brightness == 0)
          infoSettings.lcd_brightness = 1; //In Normal it should not be off. Set back to 5%

        char tempstr[8];
        sprintf(tempstr, (char *)textSelect(LABEL_PERCENT_VALUE), LCD_BRIGHTNESS[infoSettings.lcd_brightness]);
        setDynamicTextValue(key_val, tempstr);
        Set_LCD_Brightness(LCD_BRIGHTNESS[infoSettings.lcd_brightness]);
        break;
      }

      case SKEY_LCD_IDLE_BRIGTHNESS:
      {
        infoSettings.lcd_idle_brightness = (infoSettings.lcd_idle_brightness + 1) % ITEM_BRIGHTNESS_NUM;
        char tempstr[8];
        sprintf(tempstr,(char *)textSelect(LABEL_PERCENT_VALUE), LCD_BRIGHTNESS[infoSettings.lcd_idle_brightness]);
        setDynamicTextValue(key_val,tempstr);
        break;
      }

      case SKEY_LCD_IDLE_DELAY:
        infoSettings.lcd_idle_timer = (infoSettings.lcd_idle_timer + 1) % ITEM_SECONDS_NUM;
        settingPage[item_index].valueLabel = itemDimTime[infoSettings.lcd_idle_timer];
        break;
    #endif //LCD_LED_PWM_CHANNEL

    case SKEY_START_GCODE_ENABLED:
      infoSettings.send_start_gcode = (infoSettings.send_start_gcode + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.send_start_gcode];
      break;

    case SKEY_END_GCODE_ENABLED:
      infoSettings.send_end_gcode = (infoSettings.send_end_gcode + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.send_end_gcode];
      break;

    case SKEY_CANCEL_GCODE_ENABLED:
      infoSettings.send_cancel_gcode = (infoSettings.send_cancel_gcode + 1) % ITEM_TOGGLE_NUM;
      settingPage[item_index].icon = iconToggle[infoSettings.send_cancel_gcode];
      break;

    case SKEY_RESET_SETTINGS:
      setDialogText(LABEL_SETTINGS_RESET, LABEL_SETTINGS_RESET_INFO, LABEL_CONFIRM, LABEL_CANCEL);
      showDialog(DIALOG_TYPE_ALERT, resetSettings, NULL, NULL);
      break;

    default:
      return;
  }

  featureSettingsItems.items[key_val] = settingPage[item_index];
} //updateFeatureSettings

//
//load values on page change and reload
//
void loadFeatureSettings()
{
  for (uint8_t i = 0; i < LISTITEM_PER_PAGE; i++)
  {
    uint8_t item_index = fe_cur_page * LISTITEM_PER_PAGE + i;

    if (item_index < SKEY_COUNT)
    {
      switch (item_index)
      {
        case SKEY_STATUS_SCREEN:
          settingPage[item_index].icon = iconToggle[infoSettings.status_screen];
          break;

        case SKEY_TERMINAL_ACK:
          settingPage[item_index].icon = iconToggle[infoSettings.terminalACK];
          break;

        case SKEY_INVERT_X_AXIS:
          settingPage[item_index].icon = iconToggle[infoSettings.invert_axis[X_AXIS]];
          break;

        case SKEY_INVERT_Y_AXIS:
          settingPage[item_index].icon = iconToggle[infoSettings.invert_axis[Y_AXIS]];
          break;

        case SKEY_INVERT_Z_AXIS:
          settingPage[item_index].icon = iconToggle[infoSettings.invert_axis[Z_AXIS]];
          break;

        case SKEY_PERSISTENT_INFO:
          settingPage[item_index].icon = iconToggle[infoSettings.persistent_info];
          break;

        case SKEY_FILE_LIST_MODE:
          settingPage[item_index].icon = iconToggle[infoSettings.file_listmode];
          break;

        case SKEY_ACK_NOTIFICATION:
          setDynamicTextValue(i, (char *)itemNotificationType[infoSettings.ack_notification]);
          break;

        case SKEY_DEFAULT_MODE:
          setDynamicTextValue(i, (char *)itemDefaultMode[infoSettings.mode]);
          break;

        case SKEY_SERIAL_ALWAYS_ON:
          settingPage[item_index].icon = iconToggle[infoSettings.serial_alwaysOn];
          break;

        #ifdef ST7920_SPI
          case SKEY_MARLIN_SHOW_TITLE:
            settingPage[item_index].icon = iconToggle[infoSettings.marlin_mode_showtitle];
            break;

          case SKEY_MARLIN_FULLSCREEN:
            settingPage[item_index].icon = iconToggle[infoSettings.marlin_mode_fullscreen];
            break;

          case SKEY_MARLIN_TYPE:
            setDynamicTextValue(i, (char *)itemMarlinType[infoSettings.marlin_type]);
            break;
        #endif

        case SKEY_SPEED:
          settingPage[item_index].valueLabel = itemSpeed[infoSettings.move_speed].label;
          break;

        case SKEY_AUTO_LOAD_LEVELING:
          settingPage[item_index].icon = iconToggle[infoSettings.auto_load_leveling];
          break;

        case SKEY_TOUCHMI_SENSOR:
          settingPage[item_index].icon = iconToggle[infoSettings.touchmi_sensor];
          break;

        case SKEY_ONBOARD_SD_SUPPORT:
          settingPage[item_index].valueLabel = itemToggleAuto[infoSettings.onboardSD];
          break;

        case SKEY_M27_ALWAYS_ACTIVE:
          settingPage[item_index].icon = iconToggle[infoSettings.m27_active];
          break;

        case SKEY_LONG_FILENAME_SUPPORT:
          settingPage[item_index].valueLabel = itemToggleAuto[infoSettings.longFileName];
          break;

        case SKEY_FAN_SPEED_PERCENT:
          settingPage[item_index].icon = iconToggle[infoSettings.fan_percentage];
          break;

        case SKEY_XY_OFFSET_PROBING:
          settingPage[item_index].icon = iconToggle[infoSettings.xy_offset_probing];
          break;

        case SKEY_Z_STEPPERS_ALIGNMENT:
          settingPage[item_index].icon = iconToggle[infoSettings.z_steppers_alignment];
          break;

        #ifdef PS_ON_PIN
          case SKEY_PS_ON:
            settingPage[item_index].valueLabel = itemToggleAuto[infoSettings.auto_off];
            break;

          case SKEY_PS_ON_ACTIVE_HIGH:
            settingPage[item_index].icon = iconToggle[infoSettings.powerloss_invert];
            break;
        #endif

        #ifdef FIL_RUNOUT_PIN
          case SKEY_FIL_RUNOUT:
            settingPage[item_index].valueLabel = itemToggleSmart[infoSettings.runout];
            break;

          case SKEY_FIL_RUNOUT_INVERTING:
            settingPage[item_index].icon = iconToggle[infoSettings.runout_invert];
            break;
        #endif

        case SKEY_PL_RECOVERY_EN:
          settingPage[item_index].icon = iconToggle[infoSettings.powerloss_en];
          break;

        case SKEY_PL_RECOVERY_HOME:
          settingPage[item_index].icon = iconToggle[infoSettings.powerloss_home];
          break;

        case SKEY_BTT_MINI_UPS:
          settingPage[item_index].icon = iconToggle[infoSettings.btt_ups];
          break;

        #ifdef LED_COLOR_PIN
          case SKEY_KNOB_LED_COLOR:
            settingPage[item_index].valueLabel = itemLedcolor[infoSettings.knob_led_color];
            featureSettingsItems.items[i] = settingPage[item_index];
            break;

          #ifdef LCD_LED_PWM_CHANNEL
            case SKEY_KNOB_LED_IDLE:
              settingPage[item_index].icon = iconToggle[infoSettings.knob_led_idle];
              break;
          #endif
        #endif

        #ifdef LCD_LED_PWM_CHANNEL
          case SKEY_LCD_BRIGHTNESS:
          {
            char tempstr[8];
            sprintf(tempstr, (char *)textSelect(LABEL_PERCENT_VALUE), LCD_BRIGHTNESS[infoSettings.lcd_brightness]);
            setDynamicTextValue(i, tempstr);
            break;
          }

          case SKEY_LCD_IDLE_BRIGTHNESS:
          {
            char tempstr[8];
            sprintf(tempstr, (char *)textSelect(LABEL_PERCENT_VALUE), LCD_BRIGHTNESS[infoSettings.lcd_idle_brightness]);
            setDynamicTextValue(i, tempstr);
            break;
          }

          case SKEY_LCD_IDLE_DELAY:
            settingPage[item_index].valueLabel = itemDimTime[infoSettings.lcd_idle_timer];
            break;
        #endif //LCD_LED_PWM_CHANNEL

        case SKEY_START_GCODE_ENABLED:
          settingPage[item_index].icon = iconToggle[infoSettings.send_start_gcode];
          break;

        case SKEY_END_GCODE_ENABLED:
          settingPage[item_index].icon = iconToggle[infoSettings.send_end_gcode];
          break;

        case SKEY_CANCEL_GCODE_ENABLED:
          settingPage[item_index].icon = iconToggle[infoSettings.send_cancel_gcode];
          break;

        case SKEY_RESET_SETTINGS:
          break;

        default:
          break;
      }

      featureSettingsItems.items[i] = settingPage[item_index];
    }
    else
    {
      featureSettingsItems.items[i].icon = ICONCHAR_BACKGROUND;
    }
  }
  // set page up down button according to page count and current page
  if (SKEY_COUNT <= LISTITEM_PER_PAGE)
  {
    featureSettingsItems.items[5].icon = ICONCHAR_BACKGROUND;
    featureSettingsItems.items[6].icon = ICONCHAR_BACKGROUND;
  }
  else
  {
    if (fe_cur_page == 0)
    {
      featureSettingsItems.items[5].icon = ICONCHAR_BACKGROUND;
      featureSettingsItems.items[6].icon = ICONCHAR_PAGEDOWN;
    }
    else if (fe_cur_page == (FE_PAGE_COUNT - 1))
    {
      featureSettingsItems.items[5].icon = ICONCHAR_PAGEUP;
      featureSettingsItems.items[6].icon = ICONCHAR_BACKGROUND;
    }
    else
    {
      featureSettingsItems.items[5].icon = ICONCHAR_PAGEUP;
      featureSettingsItems.items[6].icon = ICONCHAR_PAGEDOWN;
    }
  }
  //menuDrawListItem(&featureSettingsItems.items[5],5);
  //menuDrawListItem(&featureSettingsItems.items[6],6);

} //loadFeatureSettings

void menuFeatureSettings(void)
{
  KEY_VALUES key_num = KEY_IDLE;
  SETTINGS now = infoSettings;

  loadFeatureSettings();
  menuDrawListPage(&featureSettingsItems);

  while (infoMenu.menu[infoMenu.cur] == menuFeatureSettings)
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_5:
        if (FE_PAGE_COUNT > 1 && fe_cur_page > 0)
        {
          fe_cur_page--;
          loadFeatureSettings();
          menuRefreshListPage();
        }
        break;

      case KEY_ICON_6:
        if (FE_PAGE_COUNT > 1 && fe_cur_page < FE_PAGE_COUNT - 1)
        {
          fe_cur_page++;
          loadFeatureSettings();
          menuRefreshListPage();
        }
        break;

      case KEY_ICON_7:
        fe_cur_page = 0;
        infoMenu.cur--;
        break;

      default:
        if (key_num < LISTITEM_PER_PAGE)
        {
          updateFeatureSettings(key_num);
          menuDrawListItem(&featureSettingsItems.items[key_num], key_num);
        }
        break;
    }

    loopProcess();
  }

  if (memcmp(&now, &infoSettings, sizeof(SETTINGS)))
  {
    storePara();
  }
}
