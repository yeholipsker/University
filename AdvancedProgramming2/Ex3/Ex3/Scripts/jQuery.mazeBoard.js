
(function ($) {
    var canvas;
    var RivalsCanvas;
    var context;
    var RivalsContext;
    var rows;
    var cols;
    var cellWidth;
    var cellHeight;
    var RivalcellWidth;
    var RivalcellHeight;
    var mazeDat;
    var strRow;
    var strCol;
    var xitRow;
    var xitCol;
    var playerImg = new Image();
    playerImg.src = "../Images/Mario.png";
    var exitImg = new Image();
    exitImg.src = "../Images/exit.jpg";
    var playerRowLoc;
    var playerColLoc;
    var RivalRowLoc;
    var RivalColLoc;
    var Rival;
    var Multi;
    var again = false;
    var messagesHub = $.connection.multiplayerHub;
    $.connection.hub.start().done(function () {});

    $.fn.mazeBoard = function (mazeData, startRow, startCol, exitRow, exitCol, enabled, multi, rival = "") {


        rows = mazeData.length;
        cols = mazeData[0].length;
        mazeDat = mazeData;
        strRow = startRow;
        strCol = startCol;
        xitRow = exitRow;
        xitCol = exitCol;
        if (enabled) {
            canvas = $("#mazeCanvas")[0];
            context = canvas.getContext("2d");
            context.clearRect(0, 0, canvas.width, canvas.height);
            cellWidth = canvas.width / cols;
            cellHeight = canvas.height / rows;
            playerRowLoc = strRow;
            playerColLoc = strCol;
            Rival = rival;
            Multi = multi;
            document.addEventListener('keydown', move, false);
            context.fillStyle = "#000000";
            for (var i = 0; i < rows; i++) {
                for (var j = 0; j < cols; j++) {
                    if (mazeData[i][j] == 1) {
                        context.fillRect(cellWidth * j, cellHeight * i,
                            cellWidth, cellHeight);
                    }
                }
            }
            context.drawImage(playerImg, playerColLoc * cellWidth, playerRowLoc * cellHeight, cellWidth, cellHeight);
            context.drawImage(exitImg, xitCol * cellWidth, xitRow * cellHeight, cellWidth, cellHeight);
            if (multi) {
                again = true;
            }
        }
        if (again){
            Rivalcanvas = $("#rivalsMazeCanvas")[0];
            Rivalcontext = Rivalcanvas.getContext("2d");
            Rivalcontext.clearRect(0, 0, Rivalcanvas.width, Rivalcanvas.height);
            RivalcellWidth = Rivalcanvas.width / cols;
            RivalcellHeight = Rivalcanvas.height / rows;
            RivalRowLoc = strRow;
            RivalColLoc = strCol;
            Rivalcontext.fillStyle = "#000000";
            for (var k = 0; k < rows; k++) {
                for (var l = 0; l < cols; l++) {
                    if (mazeData[k][l] == 1) {
                        Rivalcontext.fillRect(RivalcellWidth * l, RivalcellHeight * k,
                            RivalcellWidth, RivalcellHeight);
                    }
                }
            }
            Rivalcontext.drawImage(playerImg, RivalColLoc * RivalcellWidth, RivalRowLoc * RivalcellHeight, RivalcellWidth, RivalcellHeight);
            Rivalcontext.drawImage(exitImg, xitCol * RivalcellWidth, xitRow * RivalcellHeight, RivalcellWidth, RivalcellHeight);
            
        }
            
        
    };
    function movePlayer(newRowLoc, newColLoc) {
        context.fillStyle = "#ffffff";
        context.fillRect(playerColLoc * cellWidth, playerRowLoc * cellHeight, cellWidth, cellHeight);
        context.drawImage(playerImg, newColLoc * cellWidth, newRowLoc * cellHeight, cellWidth, cellHeight);
        playerColLoc = newColLoc;
        playerRowLoc = newRowLoc;
    }
    function moveRival(newRowLoc, newColLoc) {
        Rivalcontext.fillStyle = "#ffffff";
        Rivalcontext.fillRect(RivalColLoc * RivalcellWidth, RivalRowLoc * RivalcellHeight, RivalcellWidth, RivalcellHeight);
        Rivalcontext.drawImage(playerImg, newColLoc * RivalcellWidth, newRowLoc * RivalcellHeight, RivalcellWidth, RivalcellHeight);
        RivalColLoc = newColLoc;
        RivalRowLoc = newRowLoc;
    }
    function move(event) {

        switch (event.keyCode) {
            case 37:
                if (mazeDat[playerRowLoc][playerColLoc - 1] == 0) {
                    movePlayer(playerRowLoc, playerColLoc - 1);
                    if (Multi) {
                        messagesHub.server.move(Rival,"left" );
                    }
                }

                break;
            case 38:
                if (mazeDat[playerRowLoc - 1][playerColLoc] == 0) {
                    movePlayer(playerRowLoc - 1, playerColLoc);
                    if (Multi) {
                        messagesHub.server.move( Rival, "up");
                    }
                }
                break;
            case 39:
                if (mazeDat[playerRowLoc][playerColLoc + 1] == 0) {
                    movePlayer(playerRowLoc, playerColLoc + 1);
                    if (Multi) {
                        messagesHub.server.move( Rival, "down");
                    }
                }
                break;
            case 40:
                if (mazeDat[playerRowLoc + 1][playerColLoc] == 0) {
                    movePlayer(playerRowLoc + 1, playerColLoc);
                    if (Multi) {
                        messagesHub.server.move( Rival, "right");
                    }
                }
                break;
        }
        if (playerRowLoc == xitRow && playerColLoc == xitCol) {
            document.removeEventListener('keydown', movePlayer);
            if (Multi) {
                var apiUrl = "../api/Registry/SetRank/" + sessionStorage.getItem("loggedInUser") + "/" + "Win" + "/" + "0";
                $.ajax({
                    method: "GET",
                    url: apiUrl
                }).done(function (maze) { });

            }
           
            alert("you won!! =)");
            document.onkeydown = function (e) {
                return false;
            };
           
        }
    }
    $.fn.solveMaze = function (solution) {
        movePlayer(strRow, strCol);
        var i = 0;
        var x = setInterval(function () {

            switch (solution[i]) {
                case '0':
                    movePlayer(playerRowLoc, playerColLoc - 1);
                    break;
                case '1':
                    movePlayer(playerRowLoc, playerColLoc + 1);
                    break;
                case '2':
                    movePlayer(playerRowLoc - 1, playerColLoc);
                    break;
                case '3':
                    movePlayer(playerRowLoc + 1, playerColLoc);
                    break;
            }
            i++;
        }, 200);

        document.onkeydown = function (e) {
            return false;
        };
    };



    $.fn.rivalMove = function (direction) {

        switch (direction) {
            case "left":
                if (mazeDat[RivalRowLoc][RivalColLoc - 1] == 0) {
                    moveRival(RivalRowLoc, RivalColLoc - 1);
                }

                break;
            case "up":
                if (mazeDat[RivalRowLoc - 1][RivalColLoc] == 0) {
                    moveRival(RivalRowLoc - 1, RivalColLoc);
                }
                break;
            case "right":
                if (mazeDat[RivalRowLoc][RivalColLoc + 1] == 0) {
                    moveRival(RivalRowLoc, RivalColLoc + 1);
                }
                break;
            case "down":
                if (mazeDat[RivalRowLoc + 1][RivalColLoc] == 0) {
                    moveRival(RivalRowLoc + 1, RivalColLoc);
                }
                break;
            default:
                break;
        }
        if (RivalRowLoc == xitRow && RivalColLoc == xitCol) {
            
                var apiUrl = "../api/Registry/SetRank/" + sessionStorage.getItem("loggedInUser") + "/" + "lose"+"/"+"0";
                $.ajax({
                    method: "GET",
                    url: apiUrl
                }).done(function (maze) { });
            
                alert("you Lost =(");
                document.onkeydown = function (e) {
                    return false;
                };
                    
        }

    };

})(jQuery); 
