<?php

namespace Drupal\wikisearch\Controller;

use Drupal\Core\Controller\ControllerBase;

class Wikisearch extends ControllerBase {

  /**
   * Display the markup.
   *
   * @return array
   */
  public function content() {
    return array(
      '#type' => 'markup',
      '#markup' => $this->t('Hello, World!'),
    );
  }

}
