# Amxx-Module-CustomEntityData
API for saving custom entity data easily through AMXX plugins

# Linux
Since libgcc_s.so.1 and libstdc++.so.6 bundled with HLDS for Linux are too old, install the latest GCC and place symbolic links to the respective libraries.

1. install gcc over than 11.3.1
2. command execute.

+ cd /[your hlds directory]/

+ mv libgcc_s.so.1 libgcc_s.so.1.bk
+ mv libstdc++.so.6 libstdc++.so.6.bk

+ ln -s /usr/lib/libgcc_s.so.1 libgcc_s.so.1
+ ln -s /usr/lib/libstdc++.so.6 libstdc++.so.6
