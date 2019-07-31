$(document).ready(function(){

        var url = window.location.origin;
        $.jqplot.config.enablePlugins = true;

        $.getJSON( url+"/data_analytis/sites/all/modules/custom/circle_chart/js/month/year.json", function( data ) {
            var s0 = [];
            var ticks = [];

            for(var i = 0;i<=11;i++){
                s0.push(data[i]);
            }
            for(var i = 12;i<=23;i++){
                ticks.push(data[i]);
            }
            
            plot1 = $.jqplot('chart4', [s0], {
                // Only animate if we're not using excanvas (not in IE 7 or IE 8)..
                animate: !$.jqplot.use_excanvas,
                seriesDefaults:{
                    renderer:$.jqplot.BarRenderer,
                    pointLabels: { show: true }
                },
                axes: {
                    xaxis: {
                        renderer: $.jqplot.CategoryAxisRenderer,
                        ticks: ticks
                    }
                },
                highlighter: { show: false }
            });

            $('#chart4').hide();

        });
        
        $.getJSON( url+"/data_analytis/sites/all/modules/custom/circle_chart/js/month/month.json", function( data ) {
            var s1 = [];
            var ticks = [];
            if(data.length == 24){
                for(var i = 0;i<=11;i++){
                    s1.push(data[i]);
                }
                for(var i = 12;i<=23;i++){
                    ticks.push(data[i]);
                } 
            }else{
                for(var i = 0;i<=11;i++){
                    s1.push(data[i]);
                }
                for(var i = 12;i<=23;i++){
                    ticks.push(data[i]);
                }
            }
            
            plot1 = $.jqplot('chart12', [s1], {
                // Only animate if we're not using excanvas (not in IE 7 or IE 8)..
                animate: !$.jqplot.use_excanvas,
                seriesDefaults:{
                    renderer:$.jqplot.BarRenderer,
                    pointLabels: { show: true }
                },
                axes: {
                    xaxis: {
                        renderer: $.jqplot.CategoryAxisRenderer,
                        ticks: ticks
                    }
                },
                highlighter: { show: false }
            });

        });

        $.getJSON( url+"/data_analytis/sites/all/modules/custom/circle_chart/js/month/month.json", function( data ) {
            var s2 = [];
            var ticks = [];

            for(var i = 6; i<=12; i++){
                s2.push(data[i]);
            }

            for(var i = 18; i<=24; i++){
                ticks.push(data[i]);
            }
       
            plot1 = $.jqplot('chart6', [s2], {
                // Only animate if we're not using excanvas (not in IE 7 or IE 8)..
                animate: !$.jqplot.use_excanvas,
                seriesDefaults:{
                    renderer:$.jqplot.BarRenderer,
                    pointLabels: { show: true }
                },
                axes: {
                    xaxis: {
                        renderer: $.jqplot.CategoryAxisRenderer,
                        ticks: ticks
                    }
                },
                highlighter: { show: false }
            });
            $("#chart6").hide();
        });

        $.getJSON( url+"/data_analytis/sites/all/modules/custom/circle_chart/js/month/month3.json", function( data ) {
            var s3 = [];
            var ticks = [];
            for(var i = 0;i<=2;i++){
                s3.push(data[i]);
            }
            for(var i = 3;i<=5;i++){
                ticks.push(data[i]);
            }
       
            plot1 = $.jqplot('chart3', [s3], {
                // Only animate if we're not using excanvas (not in IE 7 or IE 8)..
                animate: !$.jqplot.use_excanvas,
                seriesDefaults:{
                    renderer:$.jqplot.BarRenderer,
                    pointLabels: { show: true }
                },
                axes: {
                    xaxis: {
                        renderer: $.jqplot.CategoryAxisRenderer,
                        ticks: ticks
                    }
                },
                highlighter: { show: false }
            });
            $('#chart3').hide();

        });

        $("#select-month").change(function(){
            if($("#select-month").val() == 12){
                $("#chart6").hide();
                $("#chart3").hide();
                $("#chart4").hide();
                $("#chart12").show();
            }
            if($("#select-month").val() == 06){
                $("#chart12").hide();
                $("#chart3").hide(); 
                $("#chart4").hide();
                $("#chart6").show();      
            }
            if($("#select-month").val() == 03){
                $("#chart3").show();
                $("#chart12").hide();
                $("#chart4").hide();
                $("#chart6").hide();       
            }
            if($("#select-month").val() == 'year'){
                $("#chart4").show();
                $("#chart12").hide();
                $("#chart3").hide();
                $("#chart6").hide();       
            }
        });
});