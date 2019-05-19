(function ($) {
	
	$.get("navigationBar.html", function (data) {
		$("#nav-placeholder").replaceWith(data);

	});
})(jQuery);