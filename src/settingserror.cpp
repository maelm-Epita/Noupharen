#include "include/settingserror.hpp"

std::string GetSettingsErrorMessage(SETTINGS_ERROR err){
    switch (err){
    case SETTINGS_ERROR_SYLLABLECOUNT_MAX_MIN:
        return "Minimum syllable number greater than maximum";
    default:
        return "Not a valid error";
    };
}
