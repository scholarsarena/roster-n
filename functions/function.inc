<?php

  //  WRAPPER FUNCTION FOR ALL cURL REQUESTS
  //  $url          THE URL FOR THE REQUEST

  //  $method       THE REQUEST METHOD
  //                GET / POST
  //                DEFAULTS TO GET
  //                caSe-inSenSitive

  //  $params       ARRAY OF PARAMETERS TO BE SENT
  //                REQUIRED ONLY FOR POST METHOD CALLS
  //                DEFAULTS TO ""

  //  $contentType  WHAT IS EXPECTED CONTENTTYPE OF THE RESPONSE
  //                XML / TEXT / HTML / JSON
  //                DEFAULTS TO XML
  //                caSe-inSenSitive

  //  $showErr      WHETHER TO SHOW THE cURL ERROR WHEN THERE IS ONE
  //                true / false
  //                DEFAULTS TO false
  //                boolean value
  function fnCurl($url, $method = "GET", $headers = array(), $params = "", $contentType = "", $showErr = false) {
    switch(strtoupper($contentType)) {
      case "TEXT" : $headers[] = "Content-Type: text/plain";
                    break;

      case "HTML" : $headers[] = "Content-Type: text/html";
                    break;

      case "JSON" : $headers[] = "Content-Type: application/json";
                    break;

      default     : $headers[] = "Content-Type: text/xml";
    }

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);

    if(strtoupper($method) == "GET") {
      curl_setopt($ch, CURLOPT_HTTPGET, 1);
    }
    elseif(strtoupper($method) == "POST") {
      curl_setopt($ch, CURLOPT_POST, 1);
      curl_setopt($ch, CURLOPT_POSTFIELDS, $params);
    }
    else {
      //  METHOD NOT RECOGNIZED
    }

    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);

    $result = curl_exec($ch);

    $errNo  = curl_errno($ch);
    $error  = curl_error($ch);

    if($showErr && $errNo !== 0) {
        echo "A cURL error occurred. Details: " . $error . "(" . $errNo . ")";
        return;
    }

    curl_close($ch);
    return $result;
  }

  /*
    WRITE CONTENTS INTO A FILE

    SET THE MODE FOR WRITE
    w - WRITE, OVERWRITES ANYTHING WRITTEN WITH THIS CONTENT
    a - APPEND, ADDS CONTENT TO END OF THE FILE
  */
  function fnWriteToFile($fileName, $contents, $mode = 'w') {
    $handle = fopen($fileName, $mode);
    fwrite($handle, $contents);
    fclose($handle);
  }

  /*
    READ THE CONTENTS OF FILE AND RETURN IT
  */
  function fnReadFromFile($fileName) {
    $handle = fopen($fileName, "r");
    $contents = fread($handle, filesize($fileName));
    fclose($handle);

    return $contents;
  }
