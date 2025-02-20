#include "include/settingserror.hpp"

std::string GetSettingsErrorMessage(SETTINGS_ERROR err){
    switch (err){
    case SETTINGS_ERROR_NO_LETTERGROUP:
        return "No letter groups created (See Language Settings)";
    case SETTINGS_ERROR_NO_SYLLABLEPATTERN:
        return "No syllable patterns created (See Language Settings)";
    case SETTINGS_ERROR_NO_WORDGROUP:
        return "No word groups created (See Language Settings)";
    case SETTINGS_ERROR_SYLLABLECOUNT_MAX_MIN:
        return "Minimum syllable number greater than maximum";
    case SETTINGS_ERROR_SYLLABLE_PATTERN:
        return "One or multiple syllable patterns contain an unknown letter group";
    case SETTINGS_ERROR_ATTRIBUTE_ARGUMENT:
        return "One or multiple attribute arguments contain an unknown letter";
    case SETTINGS_ERROR_WORDGROUP_ATTRIBUTE_UNKNOWN:
        return "One or multiple word groups were assigned an unknown word group attribute";
    case SETTINGS_ERROR_NO_WORDGROUP_ATTRIBUTE:
        return "One or multiple word groups have no assigned word group attributes";
    default:
        return "Not a valid error";
    };
}
