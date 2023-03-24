function adjust_style() {
  // Body
  const body = document.body;
  if (body) {
    body.style.cssText = 'width: 100%; max-width: 100%; overflow: hidden';
  }

  // Content
  const content = document.getElementById('b_content');
  if (content) {
    // Welcome page
    const previewBanner = document.getElementById('underside-sydneypro-module');
    const previewCloseBtn = document.getElementById(
      'underside-sydneypromotion-close'
    );
    const forYouContent = document.getElementById('uns_section_standard');
    const discoverContent = document.getElementById('uns_section_fixedbottom');

    if (previewBanner) {
      previewBanner.style.cssText = 'margin-top: 60px';
    }
    if (previewCloseBtn) {
      previewCloseBtn.style.cssText = 'display: none';
    }
    if (forYouContent) {
      forYouContent.style.cssText = 'display: none';
    }
    if (discoverContent) {
      discoverContent.style.cssText = 'display: none';
    }

    // Header of main page
    const headerWrapper = document.getElementsByClassName('wrapper-unfixed')[0];
    const tabWrapper = document.getElementsByClassName('uds-hdr-wrapper')[0];
    const tabs = document.getElementsByClassName('uds_tab_hdr')[0];
    const insightsTab = document.getElementById('insights');

    if (headerWrapper) {
      headerWrapper.style.cssText = 'height: 40px';
    }

    if (tabWrapper) {
      tabWrapper.style.cssText =
        'height: 40px; display: flex; justify-content: center; align-items: center;';
    }

    if (insightsTab) {
      insightsTab.style.cssText = 'display: none';
    }

    // Error
    if (!previewBanner && !tabs) {
      const errorInfo = document.createElement('p');
      errorInfo.textContent = 'Not Available';
      errorInfo.style.cssText =
        'padding: 64px 32px; text-align: center; font-size: 20px; font-weight: 600; line-height: 26px;';
      content.insertBefore(errorInfo, content.firstChild);
    }
  }

  const cibSerpMainInterval = setInterval(() => {
    const cibSerpMainLoaded =
      document.getElementsByClassName('cib-serp-main')[0];
    if (cibSerpMainLoaded) {
      clearInterval(cibSerpMainInterval);
      const $conversationMain = cibSerpMainLoaded.shadowRoot.querySelector(
        '#cib-conversation-main'
      );
      if ($conversationMain) {
        $conversationMain.shadowRoot.querySelector(
          '.container-control'
        ).style.display = 'block';
      }
    }
  }, 500);

  // Compose page
  const composeWrapper = document.getElementsByClassName(
    'uds_coauthor_wrapper'
  )[0];
  const composeMain = document.getElementsByClassName('main')[0];
  const insertBtn = document.getElementById('insert_button');
  const previewText = document.getElementById('preview_text');
  const previewOptions = document.getElementsByClassName('preview-options')[0];
  if (composeWrapper) {
    composeWrapper.style.cssText = 'margin-top: -64px';
  }
  if (composeMain) {
    composeMain.style.cssText =
      'height: calc(100% - 64px); margin-top: 64px; padding: 20px 10px';
  }
  if (insertBtn) {
    insertBtn.style.cssText = 'display: none';
  }
  if (previewText) {
    previewText.style.cssText = 'height: 100%';
  }
  if (previewOptions) {
    previewOptions.style.cssText = 'bottom: 1px';
  }
}

adjust_style();
