script_folder="/home/htrq/prog/CodeAnalysis/build-debug"
echo "echo Restoring environment" > "$script_folder/deactivate_conanrunenv-debug-x86_64.sh"
for v in FONTCONFIG_PATH
do
   is_defined="true"
   value=$(printenv $v) || is_defined="" || true
   if [ -n "$value" ] || [ -n "$is_defined" ]
   then
       echo export "$v='$value'" >> "$script_folder/deactivate_conanrunenv-debug-x86_64.sh"
   else
       echo unset $v >> "$script_folder/deactivate_conanrunenv-debug-x86_64.sh"
   fi
done

export FONTCONFIG_PATH="${FONTCONFIG_PATH:-}${FONTCONFIG_PATH:+:}/home/htrq/.conan2/p/b/fontce7dca713c2c76/p/res/etc/fonts"