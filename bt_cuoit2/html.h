const char MAIN_page[] PROGMEM = R"====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        body {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh; /* Chiều cao toàn màn hình */
            margin: 0; /* Loại bỏ lề mặc định */
        }
    
        #nhietdo, #doam {
            font-size: 24px; /* Kích thước chữ tùy chỉnh */
            text-align: center; /* Căn giữa theo chiều ngang */
        }
    </style>
    
</head>
<body>
    <div>
       Nhiet do: <span id="nhietdos">0</span> °C <br>
       Do am: <span id="doams">0</span> % <br>
    </div>
    <script>
        setInterval(function() {
            getnhietdo();
            getdoam();
        }, 1000);


        function getnhietdo() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if(this.readyState == 4 && this.status == 200) {
                    document.getElementById("nhietdos").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "docnhietdo", true);
            xhttp.send();
        }


        function getdoam() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if(this.readyState == 4 && this.status == 200) {
                    document.getElementById("doams").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "docdoam", true);
            xhttp.send();
        }
    </script>
</body>
</html>
)====";