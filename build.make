api = 2
core = 7.x

; Drupal core including patches
includes[] = drupal-org-core.make

; Download the install profile and recursively build all its dependencies
projects[bmc][type] = profile
projects[bmc][download][type] = git
projects[bmc][download][branch] = master
projects[bmc][download][url] = https://github.com/sanduhrs/bmc.git
