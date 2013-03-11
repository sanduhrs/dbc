api = 2
core = 7.x

; Drupal core including patches
includes[] = drupal-org-core.make

; Download the install profile and recursively build all its dependencies
projects[dbc][type] = profile
projects[dbc][download][type] = git
projects[dbc][download][branch] = master
projects[dbc][download][url] = https://github.com/sanduhrs/dbc.git
