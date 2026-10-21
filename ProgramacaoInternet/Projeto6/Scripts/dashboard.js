/* SCRIPT DASHBOARD PAINEL*/
async function carregarDados() { //Cria a função assincrona de carregarDados
try { //Define uma seção para testar se existe erros
//const resposta - Declara a variável "resposta"
//"await fetch" - realiza requisições HTTP assíncronas, "pausando" a execução de uma função async até que o servidor responda
const resposta = await fetch("../json/dados.json?ts=" + new Date().getTime());

if (!resposta.ok) {
//throw new Error - interrompe a execução do código e lança uma exceção customizada
throw new Error("Erro HTTP: " + resposta.status);
}

const dados = await resposta.json();

document.getElementById("ramTotal").textContent = dados.memoria_ram.total_mb;
document.getElementById("ramUsada").textContent = dados.memoria_ram.usada_mb;
document.getElementById("ramLivre").textContent = dados.memoria_ram.livre_mb;

document.getElementById("discoTotal").textContent = dados.disco.total_gb;
document.getElementById("discoUsado").textContent = dados.disco.usado_gb;
document.getElementById("discoLivre").textContent = dados.disco.livre_gb;

document.getElementById("processos").textContent = dados.processos;
document.getElementById("threads").textContent = dados.threads;
document.getElementById("temperatura").textContent = dados.cpu.temperatura;

const campoTimestamp = document.getElementById("timestamp");
if (dados.timestamp) {
campoTimestamp.textContent = dados.timestamp;
} else {
campoTimestamp.textContent = "Sem timestamp no JSON";
}
//catch é utilizado para capturar e tratar erros que ocorrem dentro de um bloco código try
} catch (erro) {
console.error("Erro ao carregar dados.json:", erro);
}
}

carregarDados();
setInterval(carregarDados, 3000); //Define o internalo de tempo para carregar os dados em 3 segundos,