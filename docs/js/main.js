
$(document).ready( function() {
    $("#nav").load( "/xutest/layout/nav.html" );
    $("#aside").load( "/xutest/layout/aside.html" );
    $("#footer").load( "/xutest/layout/footer.html" );
    $("#footer").load( "/xutest/layout/footer.html" );

    $("main").append( "<span id='top-icon'></span>" );

    $("#top-icon").load( "/xutest/layout/top-icon.html" );
    
    $("pre code").each( function( index, element ) {
        Prism.highlightElement( element );
    } );
} );