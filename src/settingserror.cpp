#include "include/settingserror.hpp"

std::string GetSettingsErrorMessage(SETTINGS_ERROR err){
    switch (err){
    case SETTINGS_ERROR_SYLLABLECOUNT_MAX_MIN:
        return "Minimum syllable number greater than maximum";
    case SETTINGS_ERROR_SYLLABLE_PATTERN:
        return "One or multiple syllable patterns contain an unknown letter";
    case SETTINGS_ERROR_ATTRIBUTE_ARGUMENT:
        return "One or multiple attribute arguments contain an unknown letter";
    case SETTINGS_ERROR_WORDGROUP_ATTRIBUTE:
        return "One or multiple word groups were assigned an unknown word group attribute";
    default:
        return "Not a valid error";
    };
}
