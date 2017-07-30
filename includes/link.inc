<?php
  class Link {

    var $url;
    var $created;
    var $changed;
    var $searched;

    function __construct($url, $searched = FALSE) {
      $this->url = $url;
      $this->created = REQUEST_TIME;
      $this->changed = REQUEST_TIME;
      $this->searched = $searched;
    }

    function clean() {
      $string = str_split($this->url);
      // Check the first character to see what we are dealing with.
      switch ($string[0]) {
        case '#':
          // This is a anchor link from the same page. We don't want to save this.
          $this->url = NULL;
          break;

        case '/':
          // Check to see first if the link is something like '//wikimediafoundation.org/blah'.
          if($string[1] == '/') {
            // not sure why these links are formatted like this,but they seem like valid links jus missing the 'http:'
            $this->url = 'http:' . $this->url;
          }

          // If we're here, then that means it should be a subpage. Add the base and return it.
          $this->url = "http://en.wikipedia.org$this->url";
          break;

        default:
          // Do nothing right now.
          break;
      }
    }

    function validate() {
      // @TODO
      // Make sure it's not in the searched table already.
    }

    function parse() {
      // Grab teh content of the page and store it in the database.
      // Mabye in the future use mongo db?
      // @TODO
    }

    function print_url() {
      drush_print($this->url);
    }
  } // End Class
