#pragma once

#define UTIL_LOG_NULL(CategoryName, Verbosity, NullItem) \
    UE_LOG(CategoryName, Verbosity, TEXT("%s is nullptr."), TEXT(#NullItem));

#define UTIL_IF_NULL_LOG_AND_RETURN(CategoryName, Verbosity, NullItem) \
    if (!NullItem) {                                                   \
        UTIL_LOG_NULL(CategoryName, Verbosity, NullItem)               \
        return;                                                        \
    }

#define UTIL_IF_NULL_LOG_AND_RETURN_VALUE(CategoryName, Verbosity, NullItem, \
                                          ReturnValue)                       \
    if (!NullItem) {                                                         \
        UTIL_LOG_NULL(CategoryName, Verbosity, NullItem)                     \
        return ReturnValue;                                                  \
    }

#define UTIL_LOG_AND_RETURN_IF(Condition, CategoryName, Verbosity, Message) \
    if (Condition) {                                                        \
        UE_LOG(CategoryName, Verbosity, TEXT(Message));                     \
        return;                                                             \
    }

#define UTIL_LOG_AND_RETURN_VALUE_IF(Condition, CategoryName, Verbosity, \
                                     Message, ReturnValue)               \
    if (Condition) {                                                     \
        UE_LOG(CategoryName, Verbosity, TEXT(Message));                  \
        return ReturnValue;                                              \
    }

#define UTIL_RETURN_IF(Condition) \
    if (Condition) {              \
        return;                   \
    }

#define UTIL_RETURN_VALUE_IF(Condition, ReturnValue) \
    if (Condition) {                                 \
        return ReturnValue;                          \
    }

#define UTIL_CONTINUE_IF(Condition) \
    if (Condition) {                \
        continue;                   \
    }
