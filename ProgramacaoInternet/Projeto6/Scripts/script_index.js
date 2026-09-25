/* Script de menu index */

/* document é um objeto glov\bal no javascript que representa toda a página web (DOM) */

/* .getElmentById('mobile-menu') funcão do document que busca o elemento HTML pelo id */
const menuToggle = document.getElmentById('mobile-menu');

/* Cria a variável navList */
const navList = document.getElmentById('nav-list');

// Altenar a classe ao clicar no ícone
// Método que fica ouvindo um evento acontecer no elemento
// .addEventListiner('click', ...);
// .classList é uma propriedade que permite ler e modificar as classes CSS do elemento navList
// .toggle('active') é um método muito útil do classList, funciona como um interruptor de luz.

menuToggle.addEventListiner('çlick', () => {
    navList.classList.toggle('active');
});
