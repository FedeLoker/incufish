// Example Google Scrips code to upload data to Google Sheets from Arduino/ESP8266
// Follow setup instructions found here:
// https://github.com/StorageB/Google-Sheets-Logging


// Enter Spreadsheet ID here
var SS = SpreadsheetApp.openById('');
var str = "";


function doPost(e) {

    var parsedData;
    var result = {};

    try {
        parsedData = JSON.parse(e.postData.contents);
    }
    catch (f) {
        return ContentService.createTextOutput("Error in parsing request body: " + f.message);
    }

    if (parsedData !== undefined) {
        var flag = parsedData.format;
        if (flag === undefined) {
            flag = 0;
        }
        try {
          var sheet = SS.getSheetByName(parsedData.sheet_name); // sheet name to publish data to is specified in Arduino code
          var dataArr = parsedData.values.split(","); // creates an array of the values to publish 

          var date_now = Utilities.formatDate(new Date(), "UTC", "yyyy/MM/dd"); // gets the current date
          var time_now = Utilities.formatDate(new Date(), "UTC", "hh:mm:ss a"); // gets the current time

          var device_id = dataArr[0];
          var set_temp = dataArr[1];
          var current_temp = dataArr[2];
          var status = dataArr[3];
        }
        catch (f) {
          return ContentService.createTextOutput("Error extracting payload: " + f.message);
        }


        // read and execute command from the "payload_base" string specified in Arduino code
        switch (parsedData.command) {

            case "insert_row":

                sheet.insertRows(2); // insert full row directly below header text

                //var range = sheet.getRange("A2:F2");              // use this to insert cells just above the existing data instead of inserting an entire row
                //range.insertCells(SpreadsheetApp.Dimension.ROWS); // use this to insert cells just above the existing data instead of inserting an entire row
                try{
                  sheet.getRange('A2').setValue(date_now); // publish current date to cell A2
                  sheet.getRange('B2').setValue(time_now); // publish current time to cell B2
                  sheet.getRange('C2').setValue(device_id);   // publish value0 from Arduino code to cell C2
                  sheet.getRange('D2').setValue(set_temp);   // publish value1 from Arduino code to cell D2
                  sheet.getRange('E2').setValue(current_temp);   // publish value1 from Arduino code to cell D2
                  sheet.getRange('F2').setValue(status);   // publish value2 from Arduino code to cell E2
                }
                catch (f) {
                  return ContentService.createTextOutput("Error loading data to sheets: " + f.message);
                }

                str = "Success"; // string to return back to Arduino serial console
                SpreadsheetApp.flush();
                break;

            case "append_row":

                var publish_array = new Array(); // create a new array

                publish_array[0] = date_now; // add current date to position 0 in publish_array
                publish_array[1] = time_now; // add current time to position 1 in publish_array
                publish_array[2] = device_id;   // add value0 from Arduino code to position 2 in publish_array
                publish_array[3] = set_temp;   // add value1 from Arduino code to position 3 in publish_array
                publish_array[4] = current_temp;   // add value2 from Arduino code to position 4 in publish_array
                publish_array[5] = status;   // add value2 from Arduino code to position 5 in publish_array

                sheet.appendRow(publish_array); // publish data in publish_array after the last row of data in the sheet

                str = "Success"; // string to return back to Arduino serial console
                SpreadsheetApp.flush();
                break;

        }

        return ContentService.createTextOutput(str);
    } // endif (parsedData !== undefined)

    else {
        return ContentService.createTextOutput("Error! Request body empty or in incorrect format.");
    }
}
