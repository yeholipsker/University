//add navigation bar
$(function () {
    if (sessionStorage.getItem("loggedInUser") === null) {
        $("#nav-placeholder").load("navigationbar.html");
    }
    else {
        $("#nav-placeholder").load("SignedNavBar.html");
    }
});

var vm = new AppViewModel();
var messagesHub = $.connection.multiplayerHub;

var self = sessionStorage.getItem("loggedInUser");
$(function () {
    $.connection.hub.start().done(function () {
        messagesHub.server.connect(self);
    });
});

var rival;





ko.validation.registerExtenders();

function AppViewModel() {
    var that = this;
    this.Name = ko.observable("").extend({ required: { message: "please enter The Game's Name" } });
    this.rows = ko.observable("").extend({ required: { message: "Please enter number of rows" },number: true });
    this.columns = ko.observable("").extend({ required: { message: "Please enter number of columns" }, number: true });
    this.gameOptions = ko.observableArray([]);
    this.selectedGame = ko.observable("");
    this.StartBtn = function () {
        document.onkeydown = function (e) {
            return false;
        };
        messagesHub.server.generateGame(that.Name(), self, that.rows(), that.columns());
    };
    this.JoinBtn = function () {
        document.onkeydown = function (e) {
            return false;
        };
        messagesHub.server.joinGame(that.selectedGame(), self);
    };

    this.isFormValid = ko.computed(function () {

        return this.columns.isValid() && this.rows.isValid(), this.Name.isValid();
    }, this);
}
messagesHub.client.start = function  (text) {
    rival = text;
    
    alert("start playing!");
    
    document.onkeydown = function (e) {
        return true;
    };
  
    
};
messagesHub.client.move = function (text) {
    $("#rivalsMazeCanvas").rivalMove(text);
};
messagesHub.client.gotGames = function (text) {
    
    vm.gameOptions(text["games"]);
    
};

messagesHub.client.gotMaze = function (text,riv) {
    DrawMaze(text,riv);

};
function DrawMaze(text,riv) {
    var maze = text;
    var rows = maze.Rows;
    var cols = maze.Cols;
    var startRow = maze.Start.Row;
    var startCol = maze.Start.Col;
    var exitRow = maze.End.Row;
    var exitCol = maze.End.Col;
    rival = riv;
    var mazeData = new Array(rows);
    for (var i = 0; i < rows; i++) {
        mazeData[i] = new Array(cols);
    }

    var fromStr = maze.Maze.split("");

    for (var j = 0; j < rows; j++) {
        for (var k = 0; k < cols; k++) {
            mazeData[j][k] = fromStr[(j * cols) + k];
        }
    }
    
    $("#mazeCanvas").mazeBoard(mazeData, startRow, startCol, exitRow, exitCol, true, true, rival);
    $("#rivalsMazeCanvas").mazeBoard(mazeData, startRow, startCol, exitRow, exitCol, false);
}
ko.applyBindings(vm, document.getElementById("multi"));

