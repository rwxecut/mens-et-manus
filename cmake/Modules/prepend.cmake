# Copyright Ding-Yi Chen
# https://stackoverflow.com/a/27630120
#
# This function prepends each variable in a list with a prefix and puts the resulting list into RESULT_VAR.
# Usage: PREPEND(RESULT_VAR ${PREFIX} ${LIST_VAR})

FUNCTION(PREPEND result_var prefix_and_list)
    SET(listVar "")
    FOREACH(f ${ARGN})
        LIST(APPEND listVar "${prefix_and_list}/${f}")
    ENDFOREACH(f)
    SET(${result_var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)
