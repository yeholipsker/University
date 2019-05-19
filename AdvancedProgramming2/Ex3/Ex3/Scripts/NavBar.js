function AppViewModel() {
    var log = sessionStorage.getItem("loggedInUser");
    this.helloUser = ko.observable("  Hello," + log);
    var m =this.helloUser(); 
    this.logOut = function () {
       
        sessionStorage.removeItem("loggedInUser");
        window.location.href = "Maze.html";
    }
}

ko.applyBindings(new AppViewModel(), document.getElementById("nav-placeholder"));