
$(function () {
    if (sessionStorage.getItem("loggedInUser") === null) {
        $("#nav-placeholder").load("navigationbar.html");
    }
    else {
        $("#nav-placeholder").load("SignedNavBar.html");
    }
    });
 

function AppViewModel() {
    var that = this;
    this.UserName = ko.observable("");
    this.Password = ko.observable("");

    this.LogInClicked = function () {
        var str = this.UserName() + " " + this.Password();
        var apiUrl = "../api/Registry/" + str;
        $.getJSON(apiUrl).done(function (User) {

            sessionStorage.loggedInUser = User.UserName;
            window.location.href = "Maze.html";
        })
            .fail(function (jqXHR, status, errorThrown) {
                // if the page not found
                if (errorThrown == "Not Found") {
                    alert('Wrong username or password');
                }
                else {
                    alert('Failed send request to server');
                }
            });
    };
    this.isFormValid = ko.computed(function () {

        return this.Password() && this.UserName();
    }, this);
}

ko.applyBindings(new AppViewModel());