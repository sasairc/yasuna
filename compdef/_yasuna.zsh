#compdef yasuna

function _yasuna() {
    _arguments -s : \
        {-l,--list}'[print all quotes list and exit]' \
        {-n,--number}'[specify quote number]':keyword \
        {-s,--speaker}'[specify speaker]':keyword \
        {-K,--search}'[show all quotes matching regex]':keyword \
        {-f,--file}'[specfiles the dictionary file]:file:_files' \
        {-h,--help}'[display help]' \
        {-v,--version}'[output version]'
}

_yasuna
