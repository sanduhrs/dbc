; Drush build file
; See http://drush.ws/#make
; See http://drush.ws/examples/example.make

api = 2
core = 7.x

; Base
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.2"

projects[devel][subdir] = "contrib"
projects[devel][version] = "1.3"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0-beta1"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[views][subdir] = "contrib"
projects[views][version] = "3.5"

projects[migrate][subdir] = "contrib"
projects[migrate][version] = "2.5"

projects[calendar][subdir] = "contrib"
projects[calendar][version] = "3.4"

projects[link][subdir] = "contrib"
projects[link][version] = "1.1"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-unstable7"

projects[media][subdir] = "contrib"
projects[media][version] = "2.0-unstable7"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.2"

projects[remote_stream_wrapper][subdir] = "contrib"
projects[remote_stream_wrapper][version] = "1.0-beta4"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.0"

projects[countries][subdir] = "contrib"
projects[countries][version] = "2.1"

projects[countryicons][subdir] = "contrib"
projects[countryicons][version] = "2.0-beta1"

projects[flag][subdir] = "contrib"
projects[flag][version] = "2.0"

projects[field_collection][subdir] = "contrib"
projects[field_collection][version] = "1.0-beta5"
projects[field_collection][patch][1175082] = "http://drupal.org/files/field_collection-migrate-1175082-194.patch"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.1"

; Themes

; Libraries
