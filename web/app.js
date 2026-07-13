async function loadConfig()
{
    const endpointList = document.getElementById("endpointList");

    try
    {
        const response = await fetch("/api/config");

        if (!response.ok)
            throw new Error("Nie udało się pobrać konfiguracji.");

        const config = await response.json();

        endpointList.replaceChildren();

        if (config.endpoints.length === 0)
        {
            endpointList.textContent = "Brak endpointów.";
            return;
        }

        for (const endpoint of config.endpoints)
        {
            const item = document.createElement("div");

            item.textContent =
                endpoint.description +
                " | " +
                endpoint.url +
                " | interwał: " +
                endpoint.interval_ms +
                " ms | " +
                (endpoint.enabled ? "włączony" : "wyłączony");

            endpointList.appendChild(item);
        }
    }
    catch (error)
    {
        endpointList.textContent = "Błąd: " + error.message;
    }
}

document
    .getElementById("loadButton")
    .addEventListener("click", loadConfig);

loadConfig();