<?php

/**
 * @file
 * The default format for adresses.
 */

$plugin = array(
  'title' => t('Address form (country-specific)'),
  'format callback' => 'addressfield_format_address_generate',
  'type' => 'address',
  'weight' => -100,
);

/**
 * Format callback.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_format_address_generate(&$format, $address, $context = array()) {
  // We start with a reasonable default: a simple block format suitable
  // for international shipping. We extend it with country-specific heuristics
  // below.

  // The street block.
  $format['street_block'] = array(
    '#type' => 'addressfield_container',
    '#attributes' => array('class' => array('street-block')),
    '#weight' => 0,
  );
  $format['street_block']['thoroughfare'] = array(
    '#title' => t('Address 1'),
    '#tag' => 'div',
    '#attributes' => array('class' => array('thoroughfare')),
    '#size' => 30,
    // The #required will be automatically set to FALSE when processing.
    '#required' => TRUE,
  );
 // $format['street_block']['premise'] = array(
 //   '#title' => t('Address 2'),
 //   '#tag' => 'div',
 //   '#attributes' => array('class' => array('premise')),
 //   '#size' => 30,
 // );
  $format['locality_block'] = array(
    '#type' => 'addressfield_container',
    '#attributes' => array('class' => array('addressfield-container-inline', 'locality-block', 'country-' . $address['country'])),
    '#weight' => 50,
  );
  $format['locality_block']['#attached']['css'][] = drupal_get_path('module', 'addressfield') . '/addressfield.css';
 
  $format['locality_block']['locality'] = array(
    '#title' => t('City'),
    '#size' => 30,
    '#required' => TRUE,
    // '#prefix' => ' ',
    '#attributes' => array('class' => array('locality')),
  );
  $format['country'] = array(
    '#title' => t('Country'),
    '#options' => _addressfield_country_options_list(),
    '#required' => TRUE,
    '#attributes' => array('class' => array('country')),
    '#weight' => 100,
  );

  // Those countries do not seem to have a relevant postal code.
  if (in_array($address['country'], array('AF', 'AG', 'AL', 'AO', 'BB', 'BI', 'BJ', 'BO', 'BS', 'BW', 'BZ', 'CF', 'CG', 'CM', 'CO', 'DJ', 'DM', 'EG', 'ER', 'FJ', 'GD', 'GH', 'GM', 'GQ', 'GY', 'IE', 'KI', 'KM', 'KP', 'KY', 'LC', 'LY', 'ML', 'MR', 'NA', 'NR', 'RW', 'SB', 'SC', 'SL', 'SR', 'ST', 'TD', 'TG', 'TL', 'TO', 'TT', 'TV', 'TZ', 'UG', 'VC', 'VU', 'WS', 'ZW'))) {
    unset($format['locality_block']['postal_code']);

    // Remove the prefix from the first widget of the block.
    $element_children = element_children($format['locality_block']);
    $first_child = reset($element_children);
    unset($format['locality_block'][$first_child]['#prefix']);
  }

  // Those countries generally use their administrative division in postal addresses.
  if (in_array($address['country'], array('AR', 'AU', 'BE', 'BR', 'BS', 'BY', 'BZ', 'CA', 'CN', 'DO', 'EG', 'ES', 'FJ', 'FR', 'FM', 'GB', 'HN', 'ID', 'IE', 'IN', 'IT', 'JO', 'JP', 'KI', 'KN', 'KR', 'KW', 'KY', 'KZ', 'MX', 'MY', 'MZ', 'NG', 'NI', 'NL', 'NR', 'NZ', 'OM', 'PA', 'PF', 'PG', 'PH', 'PR', 'PW', 'RU', 'SM', 'SO', 'SR', 'SV', 'TH', 'TW', 'UA', 'US', 'UY', 'VE', 'VI', 'VN', 'YU', 'ZA'))) {
    $format['locality_block']['administrative_area'] = array(
      '#title' => t('State'),
      '#size' => 10,
      '#required' => TRUE,
      // '#prefix' => ' ',
      '#attributes' => array('class' => array('state')),
    );
  }

  // A few contries have a well-known list of administrative divisions.
  if ($address['country'] == 'US') {
    $format['locality_block']['administrative_area']['#options'] = array(
      ''   => t('--'),
      'AL' => t('Alabama'),
      'AK' => t('Alaska'),
      'AZ' => t('Arizona'),
      'AR' => t('Arkansas'),
      'CA' => t('California'),
      'CO' => t('Colorado'),
      'CT' => t('Connecticut'),
      'DE' => t('Delaware'),
      'DC' => t('District Of Columbia'),
      'FL' => t('Florida'),
      'GA' => t('Georgia'),
      'HI' => t('Hawaii'),
      'ID' => t('Idaho'),
      'IL' => t('Illinois'),
      'IN' => t('Indiana'),
      'IA' => t('Iowa'),
      'KS' => t('Kansas'),
      'KY' => t('Kentucky'),
      'LA' => t('Louisiana'),
      'ME' => t('Maine'),
      'MD' => t('Maryland'),
      'MA' => t('Massachusetts'),
      'MI' => t('Michigan'),
      'MN' => t('Minnesota'),
      'MS' => t('Mississippi'),
      'MO' => t('Missouri'),
      'MT' => t('Montana'),
      'NE' => t('Nebraska'),
      'NV' => t('Nevada'),
      'NH' => t('New Hampshire'),
      'NJ' => t('New Jersey'),
      'NM' => t('New Mexico'),
      'NY' => t('New York'),
      'NC' => t('North Carolina'),
      'ND' => t('North Dakota'),
      'OH' => t('Ohio'),
      'OK' => t('Oklahoma'),
      'OR' => t('Oregon'),
      'PA' => t('Pennsylvania'),
      'RI' => t('Rhode Island'),
      'SC' => t('South Carolina'),
      'SD' => t('South Dakota'),
      'TN' => t('Tennessee'),
      'TX' => t('Texas'),
      'UT' => t('Utah'),
      'VT' => t('Vermont'),
      'VA' => t('Virginia'),
      'WA' => t('Washington'),
      'WV' => t('West Virginia'),
      'WI' => t('Wisconsin'),
      'WY' => t('Wyoming'),
      ' ' => t('--'),
      'AS' => t('American Samoa'),
      'FM' => t('Federated States of Micronesia'),
      'GU' => t('Guam'),
      'MH' => t('Marshall Islands'),
      'MP' => t('Northern Mariana Islands'),
      'PW' => t('Palau'),
      'PR' => t('Puerto Rico'),
      'VI' => t('Virgin Islands'),
    );
    $format['locality_block']['postal_code']['#title'] = t('ZIP Code');
  }
  else if ($address['country'] == 'IT') {
    $format['locality_block']['administrative_area']['#options'] = array(
      ''   => t('--'),
      'AG' => 'Agrigento',
      'AL' => 'Alessandria',
      'AN' => 'Ancona',
      'AO' => 'Valle d\'Aosta/Vallée d\'Aoste',
      'AP' => 'Ascoli Piceno',
      'AQ' => 'L\'Aquila',
      'AR' => 'Arezzo',
      'AT' => 'Asti',
      'AV' => 'Avellino',
      'BA' => 'Bari',
      'BG' => 'Bergamo',
      'BI' => 'Biella',
      'BL' => 'Belluno',
      'BN' => 'Benevento',
      'BO' => 'Bologna',
      'BR' => 'Brindisi',
      'BS' => 'Brescia',
      'BT' => 'Barletta-Andria-Trani',
      'BZ' => 'Bolzano/Bozen',
      'CA' => 'Cagliari',
      'CB' => 'Campobasso',
      'CE' => 'Caserta',
      'CH' => 'Chieti',
      'CI' => 'Carbonia-Iglesias',
      'CL' => 'Caltanissetta',
      'CN' => 'Cuneo',
      'CO' => 'Como',
      'CR' => 'Cremona',
      'CS' => 'Cosenza',
      'CT' => 'Catania',
      'CZ' => 'Catanzaro',
      'EN' => 'Enna',
      'FC' => 'Forlì-Cesena',
      'FE' => 'Ferrara',
      'FG' => 'Foggia',
      'FI' => 'Firenze',
      'FM' => 'Fermo',
      'FR' => 'Frosinone',
      'GE' => 'Genova',
      'GO' => 'Gorizia',
      'GR' => 'Grosseto',
      'IM' => 'Imperia',
      'IS' => 'Isernia',
      'KR' => 'Crotone',
      'LC' => 'Lecco',
      'LE' => 'Lecce',
      'LI' => 'Livorno',
      'LO' => 'Lodi',
      'LT' => 'Latina',
      'LU' => 'Lucca',
      'MB' => 'Monza e Brianza',
      'MC' => 'Macerata',
      'ME' => 'Messina',
      'MI' => 'Milano',
      'MN' => 'Mantova',
      'MO' => 'Modena',
      'MS' => 'Massa-Carrara',
      'MT' => 'Matera',
      'NA' => 'Napoli',
      'NO' => 'Novara',
      'NU' => 'Nuoro',
      'OG' => 'Ogliastra',
      'OR' => 'Oristano',
      'OT' => 'Olbia-Tempio',
      'PA' => 'Palermo',
      'PC' => 'Piacenza',
      'PD' => 'Padova',
      'PE' => 'Pescara',
      'PG' => 'Perugia',
      'PI' => 'Pisa',
      'PN' => 'Pordenone',
      'PO' => 'Prato',
      'PR' => 'Parma',
      'PT' => 'Pistoia',
      'PU' => 'Pesaro e Urbino',
      'PV' => 'Pavia',
      'PZ' => 'Potenza',
      'RA' => 'Ravenna',
      'RC' => 'Reggio di Calabria',
      'RE' => 'Reggio nell\'Emilia',
      'RG' => 'Ragusa',
      'RI' => 'Rieti',
      'RM' => 'Roma',
      'RN' => 'Rimini',
      'RO' => 'Rovigo',
      'SA' => 'Salerno',
      'SI' => 'Siena',
      'SO' => 'Sondrio',
      'SP' => 'La Spezia',
      'SR' => 'Siracusa',
      'SS' => 'Sassari',
      'SV' => 'Savona',
      'TA' => 'Taranto',
      'TE' => 'Teramo',
      'TN' => 'Trento',
      'TO' => 'Torino',
      'TP' => 'Trapani',
      'TR' => 'Terni',
      'TS' => 'Trieste',
      'TV' => 'Treviso',
      'UD' => 'Udine',
      'VA' => 'Varese',
      'VB' => 'Verbano-Cusio-Ossola',
      'VC' => 'Vercelli',
      'VE' => 'Venezia',
      'VI' => 'Vicenza',
      'VR' => 'Verona',
      'VS' => 'Medio Campidano',
      'VT' => 'Viterbo',
      'VV' => 'Vibo Valentia',
    );
    $format['locality_block']['administrative_area']['#title'] = t('Province');
  }
  else if ($address['country'] == 'BR') {
    $format['locality_block']['administrative_area']['#options'] = array(
      ''   => t('--'),
      'AC' => t('Acre'),
      'AL' => t('Alagoas'),
      'AM' => t('Amazonas'),
      'AP' => t('Amapa'),
      'BA' => t('Bahia'),
      'CE' => t('Ceara'),
      'DF' => t('Distrito Federal'),
      'ES' => t('Espirito Santo'),
      'GO' => t('Goias'),
      'MA' => t('Maranhao'),
      'MG' => t('Minas Gerais'),
      'MS' => t('Mato Grosso do Sul'),
      'MT' => t('Mato Grosso'),
      'PA' => t('Para'),
      'PB' => t('Paraiba'),
      'PE' => t('Pernambuco'),
      'PI' => t('Piaui'),
      'PR' => t('Parana'),
      'RJ' => t('Rio de Janeiro'),
      'RN' => t('Rio Grande do Norte'),
      'RO' => t('Rondonia'),
      'RR' => t('Roraima'),
      'RS' => t('Rio Grande do Sul'),
      'SC' => t('Santa Catarina'),
      'SE' => t('Sergipe'),
      'SP' => t('Sao Paulo'),
      'TO' => t('Tocantins'),
    );
  }
  else if ($address['country'] == 'CA') {
    $format['locality_block']['administrative_area']['#options'] = array(
      ''   => t('--'),
      'AB' => t('Alberta'),
      'BC' => t('British Columbia'),
      'MB' => t('Manitoba'),
      'NB' => t('New Brunswick'),
      'NL' => t('Newfoundland'),
      'NT' => t('Northwest Territories'),
      'NS' => t('Nova Scotia'),
      'NU' => t('Nunavut'),
      'ON' => t('Ontario'),
      'PE' => t('Prince Edward Island'),
      'QC' => t('Quebec'),
      'SK' => t('Saskatchewan'),
      'YT' => t('Yukon Territory'),
    );
    $format['locality_block']['administrative_area']['#title'] = t('Province');
  }
  else if ($address['country'] == 'AU') {
    $format['locality_block']['administrative_area']['#options'] = array(
      ''   => t('--'),
      'ACT' => t('Australian Capital Territory'),
      'NSW' => t('New South Wales'),
      'NT' => t('Northern Territory'),
      'QLD' => t('Queensland'),
      'SA' => t('South Australia'),
      'TAS' => t('Tasmania'),
      'VIC' => t('Victoria'),
      'WA' => t('Western Australia'),
    );
  }
  else if ($address['country'] == 'BE') {
    $format['locality_block']['administrative_area']['#options'] = array(
      ''   => t('--'),
      'ANT' => t('Antwerp'),
      'FLB' => t('Flemish Brabant'),
      'HAI' => t('Hainaut'),
      'LIE' => t('Liège'),
      'LIM' => t('Limburg'),
      'LUX' => t('Luxemburg'),
      'NAM' => t('Namur'),                                
      'OVL' => t('East Flanders'),
      'WLB' => t('Walloon Brabant'),
      'WVL' => t('West Flanders'),
    );
  }
  else if ($address['country'] == 'VN') {
    $format['locality_block']['administrative_area']['#options'] = array(
      '' => t('--'),
      'HN' => t('Ha Noi'),
      'HCM' => t('Ho Chi Minh'),
      'DN' => t('Da Nang'),
      'HP' => t('Hai Phong'),
      'CT' => t('Can Tho'),
      'AG' => t('An Giang'),
      'BRVT' => t('Ba Ria - Vung Tau'),
      'BL' => t('Bac Lieu'),
      'BG' => t('Bac Giang'),
      'BC' => t('Bac Can'),
      'BN' => t('Bac Ninh'),
      'BT' => t('Ben Tre'),
      'BD' => t('Binh Duong'),
      'BP' => t('Binh Phuoc'),
      'BT' => t('Binh Thuan'),
      'CM' => t('Ca Mau'),
      'CB' => t('Cao Bang'),
      'DL' => t('Dac Lac'),
      'DNO' => t('Dac Nong'),
      'DB' => t('Dien Bien'),
      'DNA' => t('Dong Nai'),
      'DT' => t('Dong Thap'),
      'GL' => t('Gia Lai'),
      'HG' => t('Ha Giang'),
      'HNM' => t('Ha Nam'),
      'HT' => t('Ha Tinh'),
      'HD' => t('Hai Duong'),
      'HG' => t('Hau Giang'),
      'HB' => t('Hoa Binh'),
      'HY' => t('Hung Yen'),
      'KH' => t('Khanh Hoa'),
      'KG' => t('Kien Giang'),
      'KT' => t('Kon Tum'),
      'LC' => t('Lai Chau'),
      'LD' => t('Lam Dong'),
      'LS' => t('Lang Son'),
      'LC' => t('Lao Cai'),
      'LA' => t('Long An'),
      'ND' => t('Nam Dinh'),
      'NA' => t('Nghe An'),
      'NB' => t('Ninh Binh'),
      'NT' => t('Ninh Thuan'),
      'PT' => t('Phu Tho'),
      'PY' => t('Phu Yen'),
      'QB' => t('Quang Binh'),
      'QNA' => t('Quang Nam'),
      'QNG' => t('Quang Ngai'),
      'QNI' => t('Quang Ninh'),
      'QT' => t('Quang Tri'),
      'ST' => t('Soc Trang'),
      'SL' => t('Son La'),
      'TN' => t('Tay Ninh'),
      'TB' => t('Thai Binh'),
      'TN' => t('Thai Nguyen'),
      'TH' => t('Thanh Hoa'),
      'TTH' => t('Thua Thien - Hue'),
      'TG' => t('Tien Giang'),
      'TV' => t('Tra Vinh'),
      'TQ' => t('Tuyen Quang'),
      'VL' => t('Vinh Long'),
      'VP' => t('Vinh Phuc'),
      'YB' => t('Yen Bai')
    );
    $format['locality_block']['administrative_area']['#title'] = t('Province');
  }
  else if ($address['country'] == 'NL') {
    $format['locality_block']['administrative_area']['#options'] = array(
      ''   => t('--'),
      'DR' => t('Drenthe'),
      'FL' => t('Flevoland'),
      'FR' => t('Friesland'),
      'GE' => t('Gelderland'),
      'GR' => t('Groningen'),
      'LI' => t('Limburg'),
      'NB' => t('North Brabant'),
      'NH' => t('North Holland'),
      'OV' => t('Overijssel'),
      'UT' => t('Utrecht'),
      'ZE' => t('Zeeland'),
      'SH' => t('South Holland')
    );
    $format['locality_block']['administrative_area']['#title'] = t('Province');
  }


  // Postal code was moved here by mkchen
  $format['locality_block']['postal_code'] = array(
    '#title' => t('Postal Code'),
    '#size' => 10,
    '#required' => TRUE,
    '#attributes' => array('class' => array('postal-code')),
  );

  // Those countries tend to put the postal code after the locality.
  if (in_array($address['country'], array('AU', 'BD', 'BF', 'BH', 'BM', 'BN', 'BT', 'CA', 'FM', 'GB', 'ID', 'IN', 'JM', 'JO', 'KH', 'LB', 'LS', 'LV', 'MM', 'MN', 'MV', 'MW', 'NG', 'NP', 'NZ', 'PE', 'PK', 'PR', 'PW', 'SA', 'SG', 'SO', 'TH', 'US', 'VI', 'VG', 'VN'))) {
    // Take the widget out of the array.
    $postal_code_widget = $format['locality_block']['postal_code'];
    // $postal_code_widget['#prefix'] = ' ';
    unset($format['locality_block']['postal_code']);

    // Add it back.
    $format['locality_block']['postal_code'] = $postal_code_widget;


    // Remove the prefix from the first widget of the block.
    $element_children = element_children($format['locality_block']);
    $first_child = reset($element_children);
    unset($format['locality_block'][$first_child]['#prefix']);
  }

  // GB-specific tweaks
  if ($address['country'] == 'GB') {
    // Locality
    $format['locality_block']['locality'] = array_merge(
      $format['locality_block']['locality'],
      array(
        '#title' => t('Town/City'),
        '#weight' => 40,
        // '#prefix' => '',
        '#tag' => 'div',
      )
    );

    // Administrative
    $format['locality_block']['administrative_area'] = array_merge(
      $format['locality_block']['administrative_area'],
      array(
        '#title' => t('County'),
        '#required' => FALSE,
        '#weight' => 50,
        '#size' => 30,
        // '#prefix' => '',
        '#tag' => 'div',
      )
    );

    // Postal code
    $format['locality_block']['postal_code'] = array_merge(
      $format['locality_block']['postal_code'],
      array(
        '#title' => t('Postcode'),
        '#weight' => 60,
        // '#prefix' => '',
        '#tag' => 'div',
      )
    );
  }

  if ($context['mode'] == 'form') {
    // Provide a wrapper ID for AJAX replacement based on country selection.
    if (!isset($format['#wrapper_id'])) {
      $format['#wrapper_id'] = drupal_html_id('addressfield-wrapper');
      $format['#prefix'] = '<div id="' . $format['#wrapper_id'] . '">';
      $format['#suffix'] = '</div>';
    }

    // Form mode, move the country selector to the top of the form.
    $format['country']['#weight'] = -10;

    // Limit it to the countries supported by the widget.
    if (isset($context['field'])) {
      $format['country']['#options'] = _addressfield_country_options_list($context['field'], $context['instance']);
    }

    // AJAX enable it.
    $format['country']['#ajax'] = array(
      'callback' => 'addressfield_standard_widget_refresh',
      'wrapper' => $format['#wrapper_id'],
      'method' => 'replace',
    );
    $format['country']['#element_validate'] = array('addressfield_standard_country_validate');
    // Don't validate any element when the country is changed.
    $format['country']['#limit_validation_errors'] = array();

    if (isset($context['delta']) && $context['delta'] > 0) {
      // On subsequent elements of a field, we make the country field non
      // required and add a ' - None - ' option to it, so as to allow the
      // user to remove the address by clearing the country field.
      $format['country']['#required'] = FALSE;
      $format['country']['#empty_value'] = '';
    }
  }
}
