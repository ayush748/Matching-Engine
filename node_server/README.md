Node addon for MatchingEngine (node-server)

Prerequisites
- Node.js (v14+ recommended)
- Python 2.7 or Python 3 (for node-gyp)
- Windows Build Tools / Visual Studio (for native addon compilation)
- node-gyp (installed via npm)

Steps
1. From the repo root, install the node dependency:

   cd node_server
   npm install

   This will install `node-addon-api` and run `node-gyp rebuild` (see package.json install script).

2. To manually configure and build the addon:

   node-gyp configure
   node-gyp build

   The produced file will be in `node_server/build/Release/binding.node`.

3. Run the server:

   node index.js

Notes
- The `binding.gyp` file uses `"<!(node -p \"require('node-addon-api').include\")"` to automatically include the `node-addon-api` headers.
- If VSCode IntelliSense doesn't find `napi.h`, ensure `node_modules` exist (`npm install`) and restart the TS/CPP language servers.
