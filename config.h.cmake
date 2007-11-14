/*
  
  Copyright (c) 2007, Tim Burrell
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at 

	http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and 
  limitations under the License. 
  
*/

#cmakedefine PACKAGE "${APPLICATION_NAME}"
#cmakedefine VERSION "${APPLICATION_VERSION}"
#cmakedefine PREFIX "${CMAKE_INSTALL_PREFIX}"
#cmakedefine LOCALEDIR "${LOCALE_INSTALL_DIR}"
#cmakedefine DATADIR "${SHARE_INSTALL_PREFIX}"
#cmakedefine LIBDIR "${LIB_INSTALL_DIR}"
#cmakedefine PLUGINDIR "${PLUGIN_INSTALL_DIR}"
#cmakedefine SYSCONFDIR "${SYSCONF_INSTALL_DIR}"
