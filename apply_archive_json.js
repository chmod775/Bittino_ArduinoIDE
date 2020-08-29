const fs = require('fs');
if (process.argv.length < 4) {
	console.error("apply_archive_json.js CHECKSUM SIZE");
	return;
}

let checksum = process.argv[2];
let size = process.argv[3];

let jsonFilename = 'IDE_BoardManager/package_alienlogic_index.json';

let rawdata = fs.readFileSync(jsonFilename);
let jsonContent = JSON.parse(rawdata);

jsonContent.packages[0].platforms[0].checksum = 'SHA-256:' + checksum;
jsonContent.packages[0].platforms[0].size = size;

fs.writeFileSync(jsonFilename, JSON.stringify(jsonContent, null, 2));
