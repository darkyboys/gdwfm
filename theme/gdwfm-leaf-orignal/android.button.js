    // Dynamically add required CSS for ripple effect
    const GTG_style = document.createElement("style");
    GTG_style.innerHTML = `
      .ripple-button {
        position: relative;
        overflow: hidden;
        cursor: pointer;
        outline: none;
        -webkit-tap-highlight-color: transparent; /* Disable touch highlight */
      }
      .ripple {
        position: absolute;
        border-radius: 50%;
        transform: scale(0);
        pointer-events: none;
        transition: transform 0.8s ease-out, opacity 0.8s ease-out;
      }
    `;
    document.head.appendChild(GTG_style);

    // Function to create the ripple effect
    function GTG_createRipple(event) {
      const GTG_button = event.currentTarget;

      // If a ripple is already visible and the button is being held, don't create another
      const GTG_existingRipple = GTG_button.querySelector('.ripple');
      if (GTG_existingRipple && !GTG_existingRipple.dataset.finished) return;

      // Create a new ripple element
      const GTG_ripple = document.createElement("span");
      GTG_ripple.classList.add("ripple");

      // Set custom ripple color from data attribute or default to darker shade
      const GTG_rippleColor = GTG_button.getAttribute("data-ripple-color") || "rgba(0, 0, 0, 0.2)";
      GTG_ripple.style.backgroundColor = GTG_rippleColor;
      GTG_ripple.style.boxShadow = `0 0 10px 5px ${GTG_rippleColor}`;

      // Get button dimensions and position to size and place the ripple
      const GTG_rect = GTG_button.getBoundingClientRect();
      const GTG_maxDimension = Math.max(GTG_rect.width, GTG_rect.height);

      // Set ripple size and position it based on the click/touch coordinates
      GTG_ripple.style.width = GTG_ripple.style.height = `${GTG_maxDimension}px`;
      const GTG_x = event.type.includes('touch') ? event.touches[0].clientX : event.clientX;
      const GTG_y = event.type.includes('touch') ? event.touches[0].clientY : event.clientY;
      GTG_ripple.style.left = `${GTG_x - GTG_rect.left - GTG_maxDimension / 2}px`;
      GTG_ripple.style.top = `${GTG_y - GTG_rect.top - GTG_maxDimension / 2}px`;

      // Mark this ripple as in progress
      GTG_ripple.dataset.finished = false;

      // Append the ripple to the button
      GTG_button.appendChild(GTG_ripple);

      // Force reflow to apply transition
      GTG_ripple.offsetHeight; // Trigger reflow

      // Start the ripple animation
      GTG_ripple.style.transform = 'scale(4)';
      GTG_ripple.style.opacity = '1';

      // Function to handle ripple fade-out when interaction ends
      const GTG_removeRipple = () => {
        GTG_ripple.dataset.finished = true; // Mark as finished to allow new ripples
        GTG_ripple.style.opacity = '0';
        GTG_ripple.addEventListener('transitionend', () => setTimeout(function(){GTG_ripple.remove()}, 1000));
      };

      // Remove ripple on interaction end
      GTG_button.addEventListener('mouseleave', GTG_removeRipple, { once: true });
      GTG_button.addEventListener('mouseup', GTG_removeRipple, { once: true });
      GTG_button.addEventListener('touchend', GTG_removeRipple, { once: true });
      GTG_button.addEventListener('touchcancel', GTG_removeRipple, { once: true });
    }

    // Function to apply ripple effect to specified elements with optional color
    function GTG_applyRippleEffect(selector, defaultColor = 'rgba(0, 0, 0, 0.2)') {
      // Select elements based on the provided selector
      const GTG_elements = document.querySelectorAll(selector);

      // Add ripple effect to each selected element
      GTG_elements.forEach(GTG_button => {
        GTG_button.classList.add('ripple-button');

        // Set default ripple color for this button
        if (!GTG_button.hasAttribute('data-ripple-color')) {
          GTG_button.setAttribute('data-ripple-color', defaultColor);
        }

        // Add event listeners for ripple effect
        GTG_button.addEventListener('mousedown', GTG_createRipple);
        GTG_button.addEventListener('touchstart', GTG_createRipple);
      });
    }

    // Apply ripple effect to all button elements by default
    // GTG_applyRippleEffect('h1', 'blue')
    
    // You can also apply to other elements with a different color
    // GTG_applyRippleEffect('.custom-container button', 'rgba(0, 255, 0, 0.6)');