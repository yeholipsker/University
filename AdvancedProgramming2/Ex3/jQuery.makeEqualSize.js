(function ($) {
	$.fn.makeEqualSize = function () {
		var maxHeight = 0;
		var maxWidth = 0;

		this.each(function () {
			var currHeight = $(this).height();
			var currWidth = $(this).width();

			if (currHeight > maxHeight)
				maxHeight = currHeight;
			if (currWidth > maxWidth)
				maxWidth = currWidth;
		});

		this.each(function () {
			$(this).height(maxHeight);
			$(this).width(maxWidth);
		}); return this;
	};
})(jQuery);