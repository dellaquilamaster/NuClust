###
###
###

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
export NuClustSrc=${DIR}/
export PATH=${NuClustSrc}:$PATH

export LD_LIBRARY_PATH=$NuClustSrc/lib:$LD_LIBRARY_PATH
