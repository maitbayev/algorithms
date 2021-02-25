alias g11="g++ -std=c++17 -Wall -Wextra -O2 -Wno-sign-compare"
alias coder="~/Dev/coder"
alias LensAutomation="~/Snapchat/Dev/LensCore/LensAutomation/build/LensAutomation"

export ANDROID_HOME="/Users/maitbayev/Library/Android/sdk"
export JAVA_HOME="Library/Java/JavaVirtualMachines/adoptopenjdk-8.jdk"

export PATH="/Users/maitbayev/Library/Python/3.7/bin:$PATH"
export PATH="/Users/maitbayev/Library/Android/sdk/platform-tools:$PATH"
export PATH="/usr/local/sbin:$PATH"

autoload -z edit-command-line
zle -N edit-command-line
bindkey "^X^E" edit-command-line

# The next line updates PATH for the Google Cloud SDK.
if [ -f '/Users/maitbayev/google-cloud-sdk/path.zsh.inc' ]; then . '/Users/maitbayev/google-cloud-sdk/path.zsh.inc'; fi

# The next line enables shell command completion for gcloud.
if [ -f '/Users/maitbayev/google-cloud-sdk/completion.zsh.inc' ]; then . '/Users/maitbayev/google-cloud-sdk/completion.zsh.inc'; fi

