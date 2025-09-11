
$(document).ready( function() {
    $("#nav").load( "/cbtest/layout/nav.html" );
    $("#aside").load( "/cbtest/layout/aside.html" );
    $("#footer").load( "/cbtest/layout/footer.html" );
    $("#footer").load( "/cbtest/layout/footer.html" );

    $("main").append( "<span id='top-icon'></span>" );

    $("#top-icon").load( "/cbtest/layout/top-icon.html" );
    
    $("pre code").each( function( index, element ) {
        Prism.highlightElement( element );
    } );
} );